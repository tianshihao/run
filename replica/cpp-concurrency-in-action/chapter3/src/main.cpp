#include <algorithm>
#include <list>
#include <mutex>

/**************** Listing 3.1 Protecting a list with a mutex. ****************/

std::list<int> some_list;
std::mutex some_mutex;

// This is the simplest thread-safe doubly linked list operation.
// Have a single mutex that protects the entire list.
void Add2List(int new_value) {
  // The use of std::lock_guard<std::mutex> in this function means that the
  // accesses in this function are mutually exclusive.
  // Use mutex to protected the entire list.
  std::lock_guard<std::mutex> guard{some_mutex};
  some_list.push_back(new_value);

  return;
}

// This is the simplest thread-safe doubly linked list operation.
bool ListContains(int value_to_find) {
  std::lock_guard<std::mutex> guard{some_mutex};
  return std::find(some_list.begin(), some_list.end(), value_to_find) !=
         some_list.end();
}

/***** Listing 3.2 Accidentally passing out a reference to protected data *****/

class SomeData {
  int a;
  std::string b;

 public:
  void DoSomething() {}
};

class DataWrapper {
 private:
  SomeData data;
  std::mutex m;

 public:
  template <typename Function>
  void ProcessData(Function func) {
    std::lock_guard<std::mutex> l{m};
    // Passing protected data to user-supplied function.
    func(data);

    return;
  }
};

SomeData* unprotected;

void MaliciousFunction(SomeData& protected_data) {
  unprotected = &protected_data;

  return;
}

DataWrapper x;

void Foo() {
  // Passing in a malicious function.
  x.ProcessData(MaliciousFunction);
  // Unprotected access to protected data.
  unprotected->DoSomething();
}

/*** Listing 3.6 Using std::lock() and std::lock_guard in a swap operation ***/

class SomeBigObject;

class SomeBigObject {
 private:
  std::string a_big_chunk[1000];
};

void Swap(SomeBigObject& lhs, SomeBigObject& rhs);

class X {
 private:
  SomeBigObject some_detail;
  std::mutex m;

 public:
  X(SomeBigObject const& sd) : some_detail{sd} {}

  friend void Swap(X& lhs, X& rhs) {
    // Ensure lhs and rhs are different instances.  Because attemping to acquire
    // a lock on st::mutex when you already hold it is undefined behavior.
    if (&lhs == &rhs) {
      return;
    }
    // The call to std::lock() locks the two mutexes.  Don't worry, If std::lock
    // has successfully acquired a lock on a mutex and an exception thrown when
    // it tries to acquire a lock on the other mutex, this first lock is
    // released automatically.  Yeah, all-or-nothing.
    std::lock(lhs.m, rhs.m);
    // ? Why still needs the lock_guard? Isn't std::lock() has already locked
    // ? the two mutexes?

    // Then the two std::lock_guard instances are constructed, one
    // for each mutex.  The std::adopt_lock parameter is supplied in addition to
    // the mutext to indecate to the std::lock_guard objects that the mutexes
    // are already locked, and they should adopt the ownership of existing lock
    // on the mutex rather than attemp to lock the mutex in the constructor.
    std::lock_guard<std::mutex> lock_a{lhs.m, std::adopt_lock};
    std::lock_guard<std::mutex> lock_b{rhs.m, std::adopt_lock};
    Swap(lhs.some_detail, rhs.some_detail);
  }
};

/***** Listing 3.9 Using std::lock() std::unique_lock in a swap operation *****/

class Y {
 private:
  SomeBigObject some_detail;
  std::mutex m;

 public:
  Y(SomeBigObject const& sd) : some_detail{sd} {}
  friend void Swap(Y& lhs, Y& rhs) {
    if (&lhs == &rhs) {
      return;
    }
    // std::defer_lock leaves mutexes unlocked.
    std::unique_lock<std::mutex> lock_a{lhs.m, std::defer_lock};
    std::unique_lock<std::mutex> lock_b{rhs.m, std::defer_lock};
    // Mutexes are locked here.
    std::lock(lock_a, lock_b);

    Swap(lhs.some_detail, rhs.some_detail);

    return;
  }
};

int main(int argc, char** argv) { return 0; }
