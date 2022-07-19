#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
bool ready{false};
int counter{0};

// void worker_thread() {
//   // Wait until main() sends data
//   std::unique_lock<std::mutex> lock(mtx);
//   cv.wait(lock);

//   // after the wait, we own the lock.
//   std::cout << "Worker thread is processing data\n";
//   counter += 1;

//   // Send data back to main()
//   ready = true;
//   lock.unlock();
//   cv.notify_one();
// }

// void worker_thread() {
//   std::unique_lock<std::mutex> lock(mtx);
//   while (!ready) {  // 防止虚假唤醒的循环
//     cv.wait(lock);
//   }
//   std::cout << "Worker thread is processing data\n";
//   counter += 1;
//   lock.unlock();
// }

void worker_thread() {
  std::unique_lock<std::mutex> lock(mtx);
  while (!cv.wait_for(lock, std::chrono::seconds(1), [] { return ready; })) {
    std::cout << "Waiting...\n";
  }
  std::cout << "Worker thread is processing data\n";
  counter += 1;
  lock.unlock();
}

int main() {
  std::thread worker(worker_thread);

  //... 执行一些其它操作

  // Send data to the worker thread
  {
    std::lock_guard<std::mutex> lock(mtx);
    ready = true;
    std::cout << "main() signals data ready for processing\n";
  }
  cv.notify_one();  // 通知一个等待的线程

  worker.join();  // 等待工作线程完成

  std::cout << "counter = " << counter << std::endl;
  return 0;
}
