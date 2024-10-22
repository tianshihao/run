#include <chrono>
#include <iostream>
#include <unordered_set>

int main() {
  // generate a unordered_set size 1000000
  std::unordered_set<int> s;
  for (int i = 0; i < 10; i++) {
    s.insert(i);
  }

  // insert s to s1
  auto start_copy = std::chrono::high_resolution_clock::now();
  std::unordered_set<int> s1 = s;
  auto end_copy = std::chrono::high_resolution_clock::now();
  auto copy_duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_copy - start_copy);

  auto start_move = std::chrono::high_resolution_clock::now();
  std::unordered_set<int> s2 = std::move(s);
  auto end_move = std::chrono::high_resolution_clock::now();
  auto move_duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_move - start_move);

  std::cout << "Copy duration: " << copy_duration.count() << " microseconds"
            << std::endl;
  std::cout << "Move duration: " << move_duration.count() << " microseconds"
            << std::endl;

  return 0;
}