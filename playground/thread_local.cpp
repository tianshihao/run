#include <iostream>
#include <thread>
#include <vector>

void callback(int _id) {
  std::cout << "ID: " << _id << std::endl;
  thread_local static int id = 0;

  std::cout << "Thread " << id << " is running." << std::endl;
  id = _id;

  std::cout << "Thread " << id << " is running." << std::endl;

  std::cout << "\n";
}

int main() {
  std::vector<int> ids{1, 2, 3, 4, 5};

  // Spawn 5 threads.
  std::for_each(ids.begin(), ids.end(), [](int id) {
    std::thread t(callback, id);
    t.join();
  });

  return 0;
}