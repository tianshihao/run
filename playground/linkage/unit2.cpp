#include "unit2.h"

#include <iostream>

#include "unit1.h"

namespace playground::linkage {

// Declaration variable with external linkage in current translation unit before
// using it.
extern int extern_var;
// The Definition of variable with external linkage must be done in the .cpp
// file.
int extern_var2{20};

void PrintExternalUnit2() {
  std::cout << __FILE__ << ": PrintExternalUnit2()" << std::endl;
  std::cout << "extern_var: " << extern_var << std::endl;
  std::cout << "extern_var2: " << extern_var2 << std::endl;
  std::cout << "extern_var3: " << extern_var3 << std::endl;
}

void PrintInternalUnit2() {
  std::cout << __FILE__ << ": PrintInternalUnit2()" << std::endl;
  // std::cout << "inernal_var2: " << inernal_var2 << std::endl;
  std::cout << "address of kSpecial: " << static_cast<const void*>(kSpecial)
            << std::endl;
  std::cout << "kSpecialView: " << kSpecialView << std::endl;
  std::cout << "kSpecialView.data(): " << kSpecialView.data() << std::endl;
  std::cout << "kSpecialView address: " << static_cast<const void*>(&kSpecialView) << std::endl;
  std::cout << "Foo(): " << Foo() << std::endl;
}

}  // namespace playground::linkage