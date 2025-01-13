#include <iostream>
#include <memory>
#include <vector>

int main() {
  // default allocator for ints.
  std::allocator<int> alloc1;
  std::vector<int> v;

  // demonstrating the few directly usable members.
  static_assert(std::is_same_v<int, decltype(alloc1)::value_type>);
  auto *p1{alloc1.allocate(1)};  // space for one int.
  alloc1.deallocate(p1, 1);      // and it is gone.

  using traits_t1 = std::allocator_traits<decltype(alloc1)>;
  p1 = traits_t1::allocate(alloc1, 1);   // space for one int.
  traits_t1::construct(alloc1, p1, 42);  // in-place construction.
  std::cout << "p1 points to " << *p1 << std::endl;

  // default allocator for strings.
  std::allocator<std::string> alloc2;
  // matcing traits.
  using traits_t2 = std::allocator_traits<decltype(alloc2)>;

  // rebinding the allocator using the trait for strings gets the same type
  traits_t2::rebind_alloc<std::string> alloc_ = alloc2;

  auto p2{traits_t2::allocate(alloc2, 2)};  // space for 2 strings.

  traits_t2::construct(alloc2, p2, "hello");
  traits_t2::construct(alloc2, p2 + 1, "world");

  std::cout << "p2 points to " << *p2 << " and " << *(p2 + 1) << std::endl;

  traits_t2::destroy(alloc2, p2 + 1);
  traits_t2::destroy(alloc2, p2);
  traits_t2::deallocate(alloc2, p2, 2);

  return 0;
}