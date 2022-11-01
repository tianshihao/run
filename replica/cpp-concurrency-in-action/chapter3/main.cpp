#include <algorithm>
#include <list>
#include <memory>
#include <mutex>

#include "connection_manager.h"
#include "dns_cache.h"
#include "hierarchical_mutex.h"
#include "thread_safe_stack.h"

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

SomeData *unprotected;

void MaliciousFunction(SomeData &protected_data) {
  unprotected = &protected_data;

  return;
}

DataWrapper x;

void Foo1() {
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

void Swap(SomeBigObject &lhs, SomeBigObject &rhs);

class Connection {
 private:
  SomeBigObject some_detail;
  std::mutex m;

 public:
  Connection(SomeBigObject const &sd) : some_detail{sd} {}

  friend void Swap(Connection &lhs, Connection &rhs) {
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

class Z {
 private:
  SomeBigObject some_detail;
  std::mutex m;

 public:
  Z(SomeBigObject const &sd) : some_detail{sd} {}
  friend void Swap(Z &lhs, Z &rhs) {
    if (&lhs == &rhs) {
      return;
    }
    // std::defer_lock leaves mutexes unlocked.
    std::unique_lock<std::mutex> lock_a{lhs.m, std::defer_lock};
    std::unique_lock<std::mutex> lock_b{rhs.m, std::defer_lock};
    // Mutexes are locked here.
    std::lock(lock_a, lock_b);

    // The scoped_lock of cpp17 is recommended.
    // std::scoped_lock lck{lhs.m, rhs.m};

    Swap(lhs.some_detail, rhs.some_detail);

    return;
  }
};

/***** Listing 3.10 Locking one mutex at a time in a comparsion operator *****/

class Y {
 private:
  int some_detail;
  mutable std::mutex m;
  int GetDetail() const {
    std::lock_guard<std::mutex> lock_a{m};
    return some_detail;
  }

 public:
  Y(int sd) : some_detail{sd} {}
  // This is a bad case.  Note, however, that as well as reducing the locking
  // periods so that only one lock is held at a time, this has subtly changed
  // the semantics of the operation compared to holding both locks together.
  // The two values could have been changed in any way in between the two reads.
  // ! The values could have been swapped in between #2 and #3, and the
  // comparsion ! might returns true. ! If you don't hold the required locks for
  // the entire duration of an ! operation, you're  exposing yourself to race
  // comditions.
  friend bool operator==(Y const &lhs, Y const &rhs) {
    if (&lhs == &rhs) {
      return true;
    }

    // GetDetail() retrieves the value while protecting it with a lock.
    // ! There is only a lock at a time, Not the entire duration.
    // #2
    int const lhs_value{lhs.GetDetail()};
    // #3
    int const rhs_value{rhs.GetDetail()};

    return lhs_value == rhs_value;
  }
};

/*** Rewritting Listing 3.11 Thread-safe lazy initialization using a mutext ***/

std::shared_ptr<SomeData> resource_ptr;
std::once_flag resource_flag;
void InitResource() {
  resource_ptr.reset(new SomeData);
  return;
}

void Foo2() {
  // Initialization is called exactly once.
  std::call_once(resource_flag, InitResource);
  resource_ptr->DoSomething();
}

int main() { return 0; }
