#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

constexpr std::int8_t NUM{10};

enum class State { Thinking, Eating, Hungry };

std::vector<State> states(NUM, State::Thinking);
std::mutex the_mutex;
std::vector<std::condition_variable> self(NUM);

#define LEFT ((i + NUM - 1) % NUM)
#define RIGHT ((i + 1) % NUM)

void Test(int i) {
  if (states[i] == State::Hungry && states[LEFT] != State::Eating &&
      states[RIGHT] != State::Eating) {
    states[i] = State::Eating;
    self[i].notify_one();
  }
}

void TakeForks(int i) {
  std::unique_lock<std::mutex> lock(the_mutex);
  states[i] = State::Hungry;
  Test(i);
  while (states[i] != State::Eating) {
    self[i].wait(lock);
  }
}

void PutForks(int i) {
  std::unique_lock<std::mutex> lock(the_mutex);

  states[i] = State::Thinking;
  Test(LEFT);
  Test(RIGHT);
}

void Philosopher(int i) {
  for (int j{0}; j < 3; ++j) {
    TakeForks(i);
    std::cout << "Philosopher " << i + 1 << " is eating.\n";
    // Make a random value between -100 to 100.
    auto random_value{std::rand() % 200 - 100};
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + random_value));

    PutForks(i);
    std::cout << "Philosopher " << i + 1 << " is thinking.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(500 + random_value));
  }
  std::cout << "Philosopher " << i + 1 << " has finished dining.\n";
}

int main(int argc, char **argv) {
  std::vector<std::thread> philosophers(NUM);

  for (int i{0}; i < NUM; ++i) {
    philosophers[i] = std::thread(Philosopher, i);
    philosophers[i].join();
  }

  return 0;
}