#include <iostream>

struct TestStr {
  char data[1 << 20];
};

template <typename T>
void Forwarding(T&&);

void Handler(TestStr const&);
void Handler(TestStr&&);

int main(int argc, char** argv) {
  // ts is a lvalue.
  TestStr ts;
  // "lvalue reference\n"
  Forwarding(ts);

  // & means bind a lvalue reference of tyep 'TestStr&' to a lvalue of type
  // 'TestStr'.
  // lvalue_ref is a lvalue and it is lvalue reference of type 'TestStr'.
  TestStr& lvalue_ref{ts};
  // "lvalue reference\n"
  Forwarding(lvalue_ref);

  // Cannot bind non-const lvalue reference of type ‘TestStr&’ to an rvalue of
  // type ‘TestStr’
  // TestStr& lr2{TestStr()};
  // foo1(lr2);

  // But can bind const lvalue reference of type 'TestStr&' to an rvalue of type
  // 'TestStr'.
  // lvalue_ref_const is a lvalue and it is is rvalue reference of type
  // 'TestStr'.
  TestStr const& lvalue_ref_const{TestStr()};
  // "lvalue reference\n"
  Forwarding(lvalue_ref_const);

  // Bind rvalue reference of type 'TestStr&&' to an rvalue of type 'TestStr'.
  // lvalue_ref_const is a lvalue and it is is rvalue reference of type
  // 'TestStr'.
  // Named variables and paramters of rvalue reference type are lvalues. (You
  // can take their address.)
  TestStr&& rvalue_ref{TestStr()};
  // "lvalue reference\n"
  Forwarding(rvalue_ref);

  // "rvalue reference\n"
  Forwarding(TestStr());

  // "rvalue reference\n"
  Forwarding(std::move(ts));

  // "rvalue reference\n"
  Forwarding(std::move(lvalue_ref));

  // foo1(lvalue_ref);

  return 0;
}

template <typename T>
void Forwarding(T&& arg) {
  Handler(std::forward<T>(arg));
  return;
}

void Handler(TestStr const& o) {
  std::cout << "lvalue reference\n";
  return;
}

void Handler(TestStr&& o) {
  std::cout << "rvalue reference\n";
  return;
}
