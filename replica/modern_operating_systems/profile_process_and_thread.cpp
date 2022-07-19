// Write a program that profiles the process and thread creation time on your
// system.
//
// Hint: You can use std::chrono::high_resolution_clock to measure the time it
// takes to create a process or a thread.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

std::vector<double> process_creation_times;
std::vector<double> thread_creation_times;

void ProcessCreationTime() {
  auto start{std::chrono::high_resolution_clock::now()};
  [[maybe_unused]] auto result{std::system(R"(echo "" > /dev/null)")};
  auto end{std::chrono::high_resolution_clock::now()};
  std::chrono::duration<double> elapsed_seconds{end - start};
  std::cout.precision(17);
  // std::cout << "Process creation time: " << elapsed_seconds.count() << "s\n";
  // in ms.
  std::cout << "Process creation time: " << elapsed_seconds.count() * 1000
            << "ms\n";
  process_creation_times.push_back(elapsed_seconds.count() * 1000);
}

void ThreadCreationTime() {
  auto start{std::chrono::high_resolution_clock::now()};
  std::thread t([] {});
  t.join();
  auto end{std::chrono::high_resolution_clock::now()};
  std::chrono::duration<double> elapsed_seconds{end - start};
  std::cout.precision(17);
  // std::cout << "Thread creation time: " << elapsed_seconds.count() << "s\n";
  // in ms.
  std::cout << "Thread creation time: " << elapsed_seconds.count() * 1000
            << "ms\n";
  thread_creation_times.push_back(elapsed_seconds.count() * 1000);
}

int main() {
  // Repeat the measurements 10000 times and calculate the average.
  for (int i{0}; i < 10000; ++i) {
    ProcessCreationTime();
    ThreadCreationTime();
  }

  // Display all digits after the decimal point.
  std::cout.precision(17);
  std::cout << "Average process creation time: "
            << std::accumulate(process_creation_times.begin(),
                               process_creation_times.end(), 0.0) /
                   process_creation_times.size()
            << "ms\n";

  std::cout << "Average thread creation time: "
            << std::accumulate(thread_creation_times.begin(),
                               thread_creation_times.end(), 0.0) /
                   thread_creation_times.size()
            << "ms\n";

  // output the ratio of the average process creation time to the average thread
  // creation time.
  std::cout << "Ratio: "
            << std::accumulate(process_creation_times.begin(),
                               process_creation_times.end(), 0.0) /
                   process_creation_times.size() /
                   (std::accumulate(thread_creation_times.begin(),
                                    thread_creation_times.end(), 0.0) /
                    thread_creation_times.size())
            << '\n';

  return 0;
}