#include <iostream>

namespace replica::modern_operating_systems::peterson {
int turn;
int interested[2];

int shared = 0;

void EnterRegion(int process) {
  int other = 1 - process;
  interested[process] = true;
  turn = process;
  while (turn == process && interested[other]) {
    // busy wait
  }
}

void LeaveRegion(int process) { interested[process] = false; }

void Process0() {
  EnterRegion(0);
  shared = 5;
  LeaveRegion(0);
}

void Process1() {
  EnterRegion(1);
  std::cout << shared << std::endl;
  LeaveRegion(1);
}
}  // namespace replica::modern_operating_systems::peterson
