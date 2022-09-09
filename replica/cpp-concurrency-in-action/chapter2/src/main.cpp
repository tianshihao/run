#include <iostream>
#include <thread>
#include <vector>

// #include "../include/joining_thread.h"
#include "../include/callable_struct.h"
#include "../include/scoped_thread.h"
#include "../include/thread_guard.h"

void Oops() {
  int some_local_state{0};
  Func my_func{some_local_state};
  std::thread my_thread{my_func};
  my_thread.detach();

  // Probably my_thread is stilling running after Oops was exit.  The my_thread
  // may call DoSomething with reference to some_local_state leading to
  // undefined behavior.
  return;
}

void UsingThreadGuard() {
  int some_local_state{0};
  Func my_func{some_local_state};
  // Cause the ThreadGuard holds a reference to std::thread, we must create a
  // separate named variable first.
  std::thread t{my_func};
  // The thread guard will ensure current process waits for new thread finish,
  // thus there are no problem.
  ThreadGuard g{t};

  // Do something in current thread.

  return;
}

void g() {
  std::vector<std::thread> threads;
  for (auto i{0}; i < 20; ++i) {
    Func func{i};
    threads.emplace_back(func);
  }

  for (auto& entry : threads) {
    entry.join();
  }
}

int main(int argc, char** argv) {
  Oops();
  UsingThreadGuard();
  return 0;
}
