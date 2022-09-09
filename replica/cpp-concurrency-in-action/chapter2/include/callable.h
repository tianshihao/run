#include <iostream>

struct Func {
  int& i;

  Func(int& i_) : i{i_} {}

  void operator()() {
    for (unsigned cnt{0}; cnt < 1000000; ++cnt) {
      // Potential access to dangling reference.
      DoSomething(cnt);
    }
  }

  void DoSomething(int cnt) { std::cout << cnt << std::endl; }
};

void DoWork(int i) {
  std::cout << "Doing work " << i << std::endl;

  return;
}
