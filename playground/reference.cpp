#include <iostream>

namespace playground::reference {
void example() {
  int original_alpha{10};
  int original_beta{20};
  std::cout << "original_alpha: " << original_alpha << std::endl;
  std::cout << "original_beta: " << original_beta << std::endl;
  int& ref{original_alpha};
  ref = original_beta;
  // int const* p{&original_alpha};
  // p = &original_beta;

  std::cout << "original_alpha: " << original_alpha << std::endl;
  std::cout << "original_beta: " << original_beta << std::endl;
  std::cout << "ref: " << ref << std::endl;
  // std::cout << "p: " << *p << std::endl;
}

}  // namespace playground::reference

int main(int argc, char** argv) {
  playground::reference::example();

  return 0;
}
