#include "replica/dive-into-design-pattern/factory_method.hpp"

#include <gtest/gtest.h>

TEST(FactoryMethodTest, Produce) {
  FactoryA factory_a;
  factory_a.Produce();
  FactoryB factory_b;
  factory_b.Produce();
  factory_a.Produce();
}