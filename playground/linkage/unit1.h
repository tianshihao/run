#include <string>
namespace playground::linkage {

// If the file was included in multiple translation units, the variable would be
// defined multiple times. This would violate the one definition rule.
// int internal_i;

// internal linkage
// static int unit1_j{2};
// static std::string inernal_var2{
//     "I am static std::string inernal_var2 in define in unit1.h, internal "
//     "linkage."};

// // internal linkage
// static const int unit1_k{3};

// // internal linkage
// static constexpr int unit1_l{4};

// internal linkage.
// inline for ensuring that there is only a single copy of the variable.
// constexpr for ensuring safe initialization and destruction.
inline constexpr char kSpecial[] = "special";

inline constexpr std::string_view kSpecialView{"special"};

inline std::string_view Foo(){
  static constexpr char kHello[]{"Hello"};
  return kHello;
}

// void Foo();

// This variable has external linkage. When other source files include this,
// they can access this variable.
// The variable with external linkage could be declared multiple times in
// different translation units, but it must be defined only once.
// extern int extern_var;
extern int extern_var2;

inline std::string extern_var3{
    "I am inline std::string extern_var3 in define in unit1.h, external "
    "linkage."};

void PrintExternalUnit1();
void PrintInternalUnit1();
}  // namespace playground::linkage
