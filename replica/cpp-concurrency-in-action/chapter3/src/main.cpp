#include <algorithm>
#include <list>
#include <mutex>

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

class SomeData {
  int a;
  std::string b;

 public:
  void DoSometing();
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
