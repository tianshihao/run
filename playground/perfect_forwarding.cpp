#include <iostream>
#include <string>
#include <utility>  // for std::forward

void Print(const std::string& s) {
  std::cout << "lvalue reference: " << s << std::endl;
}

void Print(std::string&& s) {
  std::cout << "rvalue reference: " << s << std::endl;
}

// The rule of reference collapsing:
// T& & -> T&
// T&& & -> T&
// T& && -> T&
// T&& && -> T&&

// universal reference
// reference collapsing
// lvalue T& && -> T&
// rvalue T&& && -> T&&
template <typename T>
void CheckLvalueOrRvalue(T&& param) {
  if (std::is_lvalue_reference<T>::value) {
    std::cout << "lvalue" << std::endl;
  } else {
    std::cout << "rvalue" << std::endl;
  }

  Print(std::forward<T>(param));
}

// Perfect forwarding
template <typename T>
void ForwardExample(T&& param) {
  // The param itself is a lvalue, in the calling stack.
  // std::forward will preserve the lvalue or rvalue-ness of the argument
  // Forward as lvalue or as rvalue, depending on T.
  // reference collapsing
  // lvalue T& && -> T& -> forward(&) -> T& & -> T&
  // rvalue T&& && -> T&& -> forward(&&) -> T&& && -> T &&
  CheckLvalueOrRvalue(std::forward<T>(param));
}

template <typename T>
void ForwardExampleWithoutForward(T&& param) {
  // In C++, function parameters are treated as lvalues within the function
  // body. This means that even if you pass an rvalue to the function, the
  // parameter itself is considered an lvalue inside the function. Without
  // std::forward, the argument will always be lvalue
  CheckLvalueOrRvalue(param);
}

int main() {
  std::string s{"Hello"};
  CheckLvalueOrRvalue(s);             // pass lvalue
  CheckLvalueOrRvalue(std::move(s));  // pass rvalue

  ForwardExample(s);             // pass lvalue
  ForwardExample(std::move(s));  // pass rvalue

  // Only std::string is allowed.
  // ForwardExample(4);

  ForwardExampleWithoutForward(s);             // pass lvalue
  ForwardExampleWithoutForward(std::move(s));  // pass rvalue

  // The perfect forwarding mechanism depends on the type deduction of template
  // paramters. If the template parameter is explicitly specified, the type
  // deduction will not happen, the perfect forwarding will not work.
  // The T is explicitly specified as std::string, so the argument will be
  // std::string &&.
  // forward_example<std::string>(s);

  return 0;
}
