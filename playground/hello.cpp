#include <future>
#include <iostream>
#include <thread>

int main() {
  std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });

  auto f{task.get_future()};
  std::thread t(std::move(task), 1, 2);
  std::cout << f.get() << std::endl;
  if (t.joinable()) {
    t.join();
  }
}
