#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>

namespace playground::threadlocal {

void CallbackWithConstexpr(int id) {
  std::cout << "ID: " << id << std::endl;
  std::cout << "Thread " << id << " is running." << std::endl;

  // Use constexpr the mark the value is initialized at compile time, make
  // sure the variable could be fastly initialized when the program launches
  // or the thread starts.
  // But the constexpr variable could not be modified.
  [[maybe_unused]] constexpr thread_local int val{100};
  std::cout << "Val in the thread function " << val << std::endl;
  std::cout << "Val in the thread function plus the id " << val + id
            << std::endl;

  std::cout << "\n";
}

void CallbackWithConstinit(int id) {
  std::cout << "ID: " << id << std::endl;
  std::cout << "Thread " << id << " is running." << std::endl;

  // Use constinit(C++20) to mark the variable is initialized at compile time.
  // But the constinit variable could be modified.
  [[maybe_unused]] constinit thread_local int val{100};
  std::cout << "Val in the thread function " << val << std::endl;
  std::cout << "Val in the thread function plus the id " << val + id
            << std::endl;

  std::cout << "\n";

  // The following code will cause the compile error.
  // ! The constinit requires the variable could be evaluated at compile time.
  // [[maybe_unused]] constinit thread_local int{val + id};
}

class Logger {
 public:
  void Log(const std::string& message) { logs += message + "\n"; }

  void PrintLogs() { std::cout << logs; }

 private:
  thread_local static std::string logs;
};

}  // namespace playground::threadlocal

int main() {
  std::vector<int> ids{1, 2, 3, 4, 5};

  std::for_each(ids.begin(), ids.end(), [](int id) {
    std::thread t(playground::threadlocal::CallbackWithConstexpr, id);
    t.join();
  });

  std::for_each(ids.begin(), ids.end(), [](int id) {
    std::thread t(playground::threadlocal::CallbackWithConstinit, id);
    t.join();
  });

  playground::threadlocal::Logger logger1;
  logger1.Log("Log from main thread");
  logger1.PrintLogs();

  return 0;
}