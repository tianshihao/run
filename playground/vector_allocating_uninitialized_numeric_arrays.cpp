#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

template <typename Func>
void CalculateTimeCost(Func func) {
  auto start{std::chrono::high_resolution_clock::now()};

  func();

  auto end{std::chrono::high_resolution_clock::now()};
  auto duration{
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)};

  std::cout << "1 Time cost: " << duration.count() << " milliseconds"
            << std::endl;
}

void VectorValueInitialization() { std::vector<int> vec(1'000'000'000); }

// NOTES ON RUNNING THIS EXAMPLE:
// - make sure to compile it with "-O2" or "-O3"
// - you may need to reduce the vector size depending on your machine

// allocator adaptor that interposes 'construct' calls
// to convert value initialization into default initialization
// by Casey Carter (@codercasey)
template <typename T, typename Alloc = std::allocator<T>>
class default_init_allocator : public Alloc {
  using a_t = std::allocator_traits<Alloc>;

 public:
  // obtain alloc<U> where U ≠ T
  template <typename U>
  struct rebind {
    using other =
        default_init_allocator<U, typename a_t::template rebind_alloc<U>>;
  };
  // make inherited ctors visible
  using Alloc::Alloc;
  // default-construct objects
  template <typename U>
  void construct(U* ptr) noexcept(
      std::is_nothrow_default_constructible<U>::value) {  // 'placement new':
    ::new (static_cast<void*>(ptr)) U;
  }
  // construct with ctor arguments
  template <typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    a_t::construct(static_cast<Alloc&>(*this), ptr,
                   std::forward<Args>(args)...);
  }
};

void VectorDefaultInitialization() {
  std::vector<int, default_init_allocator<int>> v;
  v.resize(1'000'000'000);
}

int main() {
  CalculateTimeCost(VectorValueInitialization);
  CalculateTimeCost(VectorDefaultInitialization);

  return 0;
}
