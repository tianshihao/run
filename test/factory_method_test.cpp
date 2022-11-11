#include "ex/factory_method.hpp"

#include <gtest/gtest.h>

TEST(FactoryMethodTest, Produce) {
  FactoryA factory;
  factory.Produce();
}