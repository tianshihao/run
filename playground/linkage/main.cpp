#include <iostream>
#include <memory>
#include <vector>

#include "unit1.h"
#include "unit2.h"

std::shared_ptr<std::vector<int>> Foo() {
  static std::shared_ptr<std::vector<int>> ptr{
      std::make_shared<std::vector<int>>()};
  return ptr;
}

int main() {
  playground::linkage::PrintExternalUnit1();
  playground::linkage::PrintExternalUnit2();

  playground::linkage::PrintInternalUnit1();
  playground::linkage::PrintInternalUnit2();

  auto ptr1{Foo()};
  std::cout << "ref count: " << ptr1.use_count() << std::endl;

  thread_local constinit int i{1};

  std::cout << "i: " << i << std::endl;

  return 0;
}