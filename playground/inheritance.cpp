#include <iostream>

// Based on 64-bit machines.

// 1. Size of ABC is 16 bytes, 8 bytes for vptr, 1 byte for char a, 7 bytes
// padding.
// 2. The vptr point to the vtable of ABC, the vtable contains the address of
// the virtual functions of ABC: ~ABC(), Interface() and Foo().
// 3. The entry for Interface() in ABC's vtable is effectively a placeholder,
// since Interface() is pure virtual in ABC, it can't directly provide a valid
// function address for this slot, indicating that the derived classes must
// provide an implementation.
// 4. The destrcutor of base class must be virtual, otherwise the derived
// class destructor will not be called when deleting a derived class object
// through a base class pointer.
class ABC {
 public:
  ABC() : a{'z'} {
    std::cout << "Constructing ABC, its size is " << sizeof(ABC)
              << " byte(s).\n";
  }
  virtual ~ABC() { std::cout << "~ABC()" << std::endl; }
  virtual void Interface() = 0;
  virtual void Foo() { std::cout << "Foo() implemented by ABC" << std::endl; }

 public:
  char a;
};

// 1. Size of Derived is also 24 bytes in total, 8 for vptr, 1 for char a
// inherited from ABC, 8 added by Derived's data member double x. Taking into
// amount those members, the raw sum would be 17 bytes.  However, classes and
// structs are commonly aligned to the size of their largest member or the
// platform's word size for efficiency reasons, which in this case aligns
// naturally due to teh presence of the double and the vptr, both being 8 bytes.
// Thus, the char a is padded to 8 bytes.
class Derived : public ABC {
 public:
  Derived() : x{1.2345} {
    std::cout << "Constructing Derived, its size is " << sizeof(Derived)
              << " byte(s).\n";
  }
  ~Derived() override { std::cout << "~Derived()" << std::endl; }
  virtual void Interface() override {
    std::cout << "Interface() implemented by Derived" << std::endl;
  }
  virtual void Foo() override {
    std::cout << "Foo() implemented by Derived" << std::endl;
  }

  void Bar() {
    std::cout << "Bar(), the Derived featured function" << std::endl;
  }

 public:
  // Question: If x is int, how many bytes does Derived occupy?
  // Answer: 16 bytes, 8 for vptr, 1 for char a, 3 padding bytes, 4 for int x.
  // Question: Why the padding 3 bytes for int x, not 7?
  // Answer: The size of int is 4 bytes, so the padding is 3 bytes to make the
  // size of Derived a multiple of 8 bytes.
  double x;
};

int main() {
  Derived d;
  d.Foo();

  // Let's break down the following code.
  // 1. Object creation: The expression new Derived() creates a Derived object
  // in the heap memory. Even though the pointer p is of type ABC*, the object
  // created is of type Derived.
  // 2. Vptr initialization: When a Drived object is created, its constructor
  // initializes the object's vptr to point to Derived's vtable. The vtable
  // contains pointers to Derived's implementations of all virtual funtions.
  // 3. Dynamic dispatch of Foo(): When you call p->Foo(), the vptr in the
  // object(pointed by p) is used to look up the actual function to call via the
  // vtable associated with the object's dynamic type(Derived). Since Derived
  // overrides Foo(), the Foo() implementation in Derived is located in
  // Derived's vtable and gets executed.
  ABC* bp{new Derived()};
  bp->Foo();

  // But do not get mixed up with the code above.
  // Wrong! x is not a member of ABC.
  // The base class ABC has no knowledge of any members that are defined in its
  // derived classess, even though bp actually points to an object of type
  // Derived. This is not polymorphism.
  // std::cout << bp->x << std::endl;
  // To access x, you could downcast bp to a pointer to Derived, like this:
  std::cout << static_cast<Derived*>(bp)->x << std::endl;
  // Alternatively, if you want to ensure the type is correct at runtime, you
  // can use a dynamic cast:
  auto dp{dynamic_cast<Derived*>(bp)};
  if (dp) {
    dp->Bar();
  }

  // ! The polymorphism is implemented by the vptr and vtable mechanism.

  std::cout << bp->a << std::endl;

  return 0;
}
