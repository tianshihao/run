/**
 * @file factory_method.hpp
 * @author Shihao Tian (shihao.tian@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-11-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "utils/lazy_macro.h"

// Abstract product, For example, the vehicle.
class Product {
 public:
  Product() noexcept = default;
  Product(int id) noexcept : _id(id){};

  DECLARE_CLASS_COPY_DEFAULT(Product)
  DECLARE_CLASS_MOVE_DEFAULT(Product)

  virtual ~Product() noexcept = default;

  virtual std::string ProductInfo() noexcept = 0;

 protected:
  int _id{0};
};

// A concrete product, such as truck.
class ProductA : public Product {
 public:
  ProductA() noexcept = default;
  ProductA(int id) noexcept : Product{id} {}

  ~ProductA() noexcept override = default;

  std::string ProductInfo() noexcept override {
    return "I am ProductA with id: " + std::to_string(_id) + "\n";
  }
};

// Another concrete product, ship is also a transpot.
class ProductB : public Product {
 public:
  ProductB() noexcept = default;
  ProductB(int id) noexcept : Product{id} {}

  ~ProductB() noexcept override = default;

  std::string ProductInfo() noexcept override {
    return "I am ProductB with id: " + std::to_string(_id) + "\n";
  }
};

class Factory {
 public:
  Factory() noexcept = default;

  // Same reason with product.
  DECLARE_CLASS_COPY_DEFAULT(Factory)
  DECLARE_CLASS_MOVE_DEFAULT(Factory)

  virtual ~Factory() noexcept = default;

  // Some business.
  std::unique_ptr<Product> Produce() {
    std::unique_ptr<Product> product{GetProduct()};
    std::cout << product->ProductInfo();

    return product;
  }

 private:
  virtual std::unique_ptr<Product> GetProduct(int id = 0) = 0;
  // inferface process data
};

class FactoryA : public Factory {
 public:
  FactoryA() noexcept = default;
  ~FactoryA() noexcept override = default;

 private:
  std::unique_ptr<Product> GetProduct(int id = 0) override {
    return std::unique_ptr<ProductA>(new ProductA(id));
  }
};

class FactoryB : public Factory {
 public:
  FactoryB() noexcept = default;
  ~FactoryB() noexcept override = default;

 private:
  std::unique_ptr<Product> GetProduct(int id = 0) override {
    return std::unique_ptr<ProductB>(new ProductB(id));
  }
};
