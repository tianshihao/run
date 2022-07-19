#include <iostream>
#include <thread>
#include <vector>

#include "callable.h"
#include "joining_thread.h"
#include "parallel_accumulate.h"
#include "scoped_thread.h"
#include "thread_guard.h"

void Oops() {
  int some_local_state{0};
  FuncObj my_func_obj{some_local_state};
  std::thread my_thread{my_func_obj};
  my_thread.detach();

  // Probably my_thread is stilling running after Oops was exit.  The my_thread
  // may call DoSomething with reference to some_local_state leading to
  // undefined behavior.

  return;
}

void UsingThreadGuard() {
  int some_local_state{1};
  FuncObj my_func_obj{some_local_state};
  // Cause the ThreadGuard holds a reference to std::thread, we must create a
  // separate named variable first.
  std::thread t{my_func_obj};
  // The thread guard will ensure current process waits for new thread finish,
  // thus there are no problem.
  ThreadGuard g{t};

  // Do something in current thread.

  return;
}

void UsingScopedThread() {
  int some_local_state{2};
  // By using the new uniform initialization syntax to avoid declaring a t
  // function that takes a single paremeter.
  ScopedThread t{std::thread{FuncObj{some_local_state}}};

  // Do something in current thread.

  return;
}

void UsingJoiningThread() {
  // Func my_func_obj;
  // JoiningThread{my_func_obj, 3};

  JoiningThread{DoWork, 3};

  // Do something in current thread.

  return;
}

void SpawnThread() {
  // Putting std::thread objects in a std::vector is a step toward automating
  // the management of those threads: rather than creating separate variables
  // for those threads and joining with them directly, they can be treated as a
  // gruop.
  std::vector<std::thread> threads;
  for (auto i{0}; i < 20; ++i) {
    // Spawns threads.
    threads.emplace_back(DoWork, i);
  }

  // Call join() on each thread in turn.
  for (auto& entry : threads) {
    entry.join();
  }
}

void UsingParalleAccumulate() {
  // Spawn vector sample.
  std::vector<double> nums;

  for (int i{0}; i < 100; ++i) {
    nums.emplace_back(static_cast<double>(i));
  }

  std::cout << "Reuslt of accumulate is: "
            << std::accumulate(nums.begin(), nums.end(), 0.0) << std::endl;

  std::cout << "Result of parallel accumulate is: "
            << ParallelAccumulate(nums.begin(), nums.end(), 0.0) << std::endl;

  return;
}

int main(int argc, char** argv) {
  // Oops();
  // UsingThreadGuard();
  // UsingScopedThread();
  // SpawnThread();
  UsingParalleAccumulate();
  return 0;
}
