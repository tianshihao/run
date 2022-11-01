#pragma once

#include <numeric>
#include <thread>
#include <vector>

// ALU.
template <typename Iterator, typename T>
struct AccumulateBlock {
  void operator()(Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

// Function template.
template <typename Iterator, typename T>
T ParallelAccumulate(Iterator first, Iterator last, T init) {
  // The number of elements in range.
  unsigned long const length{std::distance(first, last)};

  if (!length) {
    return init;
  }

  // Minimum elements processing per thread.
  unsigned long const min_per_thread{25};
  // Maximum thread number.
  unsigned long const max_threads{(length + min_per_thread - 1) /
                                  min_per_thread};
  // Our hardware threads number.
  unsigned long const hardware_threads{std::thread::hardware_concurrency()};

  // Calculate how many threads we need.  This is to avoid creating 32 threads
  // on a 32-core machine when you have only five values in the range.
  unsigned long const num_threads{
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads)};

  // Then Split the data into num_threads blocks, every block has block_size
  // elements.
  unsigned long const block_size{length / num_threads};

  // num_threads threads correspond to num_threads results.
  std::vector<T> results(num_threads);

  // Thread pool. Note that you need to launch one fewer thread than
  // num_threads, because you already have one.
  std::vector<std::thread> threads(num_threads - 1);

  // Initialize thread pool.
  Iterator block_start{first};
  for (unsigned long i{0}; i < (num_threads - 1); ++i) {
    Iterator block_end{block_start};
    std::advance(block_end, block_size);

    // Every threads run a ALU that processing elements of a block.
    threads[i] = std::thread{AccumulateBlock<Iterator, T>(), block_start,
                             block_end, std::ref(results[i])};

    // Next block.
    block_start = block_end;
  }
  // Trailing block.  If the cases that the number of values doesn't divide
  // evenly.  Run on std::this_thread.
  AccumulateBlock<Iterator, T>()(block_start, last, results[num_threads - 1]);

  for (auto& entry : threads) {
    entry.join();
  }

  return std::accumulate(results.begin(), results.end(), init);
}
