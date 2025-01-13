#include "unit1.h"

#include <iostream>

namespace playground::linkage {

// Definition(assignment) of a variable with internal linkage, only once.
int extern_var{10};
// Declaration variable with external linkage in current translation unit before
// using it.
extern int extern_var2;

void PrintExternalUnit1() {
  std::cout << __FILE__ << ": PrintExternalUnit1()" << std::endl;
  std::cout << "extern_var: " << extern_var << std::endl;
  std::cout << "extern_var2: " << extern_var2 << std::endl;
  std::cout << "extern_var3: " << extern_var3 << std::endl;
}

void PrintInternalUnit1() {
  std::cout << __FILE__ << ": PrintInternalUnit1()" << std::endl;
  // std::cout << "inernal_var2: " << inernal_var2 << std::endl;
  std::cout << "address of kSpecial: " << static_cast<const void*>(kSpecial)
            << std::endl;
  std::cout << "kSpecialView: " << kSpecialView << std::endl;
  std::cout << "kSpecialView.data(): " << *kSpecialView.data() << std::endl;
  std::cout << "kSpecialView address: " << static_cast<const void*>(&kSpecialView) << std::endl;
  std::cout << "Foo(): " << Foo() << std::endl;
}

// external linkage
// void Foo() {
//   std::cout << "Foo()" << std::endl;

//   std::cout << "internal_i: " << internal_i << std::endl;
// }
}  // namespace playground::linkage