#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

std::mutex m;
std::condition_variable cv;
bool flag;

void Counter1() {
  static int cnt = 0;
  while (cnt++ < 50) {
    std::unique_lock<std::mutex> lck{m};
    cv.wait(lck, []() { return flag; });
    std::cout << "From thread 1\n";
    flag = false;
    lck.unlock();
    cv.notify_one();
  }
}

void Counter2() {
  static int cnt = 0;
  while (cnt++ < 50) {
    std::unique_lock<std::mutex> lck{m};
    cv.wait(lck, []() { return !flag; });
    std::cout << "From thread 2\n";
    flag = true;
    lck.unlock();
    cv.notify_one();
  }
}

void Func() {
  flag = true;
  std::thread t1{&Counter1};
  std::thread t2{&Counter2};
  t1.join();
  t2.join();
  return;
}

int Counter() {
  Func();
  return 0;
}