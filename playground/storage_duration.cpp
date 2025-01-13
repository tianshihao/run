#include <iostream>
#include <string_view>
#include <type_traits>

namespace playground::storage_duration {

inline constexpr std::string_view kMyString{"storage_duration"};

class Obj {
 public:
  Obj() = delete;
  explicit Obj(int id) noexcept : id_{id} {
    std::cout << "Obj::Obj(" << id_ << ")" << std::endl;
  }
  // Only for demonstration purposes. If Obj wants to have a static storage
  // duration, it must be trivially destructible.
  // Not trivially destructible.
  ~Obj() noexcept { std::cout << "Obj::~Obj(" << id_ << ")" << std::endl; }

 private:
  int id_{0};
};  // namespace playground::storage_duration

// The object in the namespace scope has static storage duration, and it lasts
// for the duration of the program.
// Only the objects with static storage duration if they are trivially
// desstructible.
Obj o{1};

// The Obj has an user-defined destructor, it is non trivally destructible.
// So Obj is firbidden to have a static storage duration.
static_assert(std::is_trivially_destructible_v<Obj> == false);

void Foo() {
  // Function-local static variables are initialized when control first passes
  // through their declaration.
  // All other objects with static storage duration are initialized as part of
  // program startup.
  static Obj o{5};
}

}  // namespace playground::storage_duration

int main() {
  std::cout << "main()" << std::endl;

  static playground::storage_duration::Obj o{2};

  auto ptr{new playground::storage_duration::Obj{4}};

  // Automatic storage duration.
  { playground::storage_duration::Obj o{3}; }

  playground::storage_duration::Foo();

  delete ptr;

  std::cout << playground::storage_duration::kMyString << std::endl;

  return 0;
}