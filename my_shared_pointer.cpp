/**
 * @file shared_pointer.cpp
 * @author tianshihao4944@outlook.com
 * @brief Inspired by
 * https://medium.com/analytics-vidhya/c-shared-ptr-and-how-to-write-your-own-d0d385c118ad
 * @version 0.1
 * @date 2022-08-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>

using my_size_t = long unsigned int;

template <typename type>
class MySharedPointer {
 private:
  my_size_t* m_ref_count{nullptr};
  type* m_pointer{nullptr};

 public:
  /******************************* Constructors. ******************************/

  // Default constructor.
  MySharedPointer() : m_ref_count{new my_size_t{0}}, m_pointer{nullptr} {}

  // Constructor.
  MySharedPointer(type* pointer)
      : m_ref_count{new my_size_t{1}}, m_pointer{pointer} {}

  /****************************** Copy semantics. *****************************/

  // Copy constructor.
  MySharedPointer(const MySharedPointer& obj)
      : m_ref_count{obj.m_ref_count}, m_pointer{obj.m_pointer} {
    if (nullptr != m_pointer) {
      ++(*m_ref_count);
    }
  }

  // Copy assignment.
  MySharedPointer& operator=(const MySharedPointer& obj) {
    // Cleanup existing data.
    __cleanup__();

    m_ref_count = obj.m_ref_count;
    m_pointer = obj.m_pointer;

    if (nullptr != m_pointer) {
      ++(*m_ref_count);
    }
  }

  /****************************** Move semantics. *****************************/

  // Move constructor.
  MySharedPointer(MySharedPointer&& dying_obj)
      : m_ref_count{dying_obj.m_ref_count}, m_pointer{dying_obj.m_pointer} {
    // Clean the dying object.
    dying_obj.m_pointer = dying_obj.m_ref_count = nullptr;
  }

  // Move assignment.
  MySharedPointer& operator=(MySharedPointer&& dying_obj) {
    // Cleanup existing data.
    __cleanup__();

    m_ref_count = dying_obj.m_ref_count;
    m_pointer = dying_obj.m_pointer;

    dying_obj.m_ref_count = dying_obj.m_pointer = nullptr;
  }

  /******************************** Destructor. *******************************/

  ~MySharedPointer() { __cleanup__(); }

  /**************************** Pointer operation. ****************************/

  type* operator->() const { return m_pointer; }

  type& operator*() const { return *m_pointer; }

  my_size_t count() const { return *m_ref_count; }

  type* get() const { return m_pointer; }

 private:
  void __cleanup__() {
    if (nullptr != m_ref_count) {
      --(*m_ref_count);
      if (0 == *m_ref_count) {
        if (nullptr != m_pointer) {
          delete m_pointer;
        }
        delete m_ref_count;
      }
    }
  }
};

// Test class.
class Box {
 public:
  int length{3};
  int width{3};
  int height{3};
};

void test1() {
  // Default constructor.
  MySharedPointer<Box> obj;
  std::cout << obj.count() << std::endl;

  // Calls constructor.
  MySharedPointer<Box> box1(new Box());
  std::cout << box1.count() << std::endl;

  std::cout << (*box1).length << std::endl;
  std::cout << box1.get()->length << std::endl;
  std::cout << box1->length << std::endl;

  // Calls copy constructor.
  MySharedPointer<Box> box2(box1);
  std::cout << box1.count() << std::endl;
  std::cout << box2.count() << std::endl;

  std::cout << (*box2).length << std::endl;
  std::cout << box2.get()->length << std::endl;
  std::cout << box2->length << std::endl;
}

int main() {
  test1();

  return 0;
}
