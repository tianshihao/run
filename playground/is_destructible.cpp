#include <iostream>
#include <string>
#include <type_traits>

namespace playground::is_destructible {

struct Foo {
  int i;
  // User-defined destructor, not trivially destructible
  ~Foo() noexcept {};
};

struct Bar {
  // Default destructor, trivially destructible
  ~Bar() = default;
};

struct Baz {
  // Non-trivial data member, not trivially destructible
  std::string str;
  ~Baz() noexcept(false) {}
};

class Base {
 public:
  // has virtual function, not trivially destructible
  virtual ~Base() = default;
};

class Derived final : public Base {
 public:
  virtual ~Derived() override final = default;
};

static_assert(std::is_destructible<std::string>::value == true);
static_assert(std::is_trivially_destructible_v<Foo> == false);

static_assert(std::is_nothrow_destructible<Foo>() == true);
static_assert(std::is_trivially_destructible<Bar>{} == true);

static_assert(std::is_nothrow_destructible<Baz>() == false);
static_assert(std::is_trivially_destructible<Baz>() == false);

static_assert(std::is_destructible<Base>() == true);
static_assert(std::is_trivially_destructible<Base>() == false);

static_assert(std::is_destructible<Derived>() == true);
static_assert(std::is_trivially_destructible<Derived>() == false);

}  // namespace playground::is_destructible
int main() {
  std::cout << "is_destructible" << std::endl;

  return 0;
}