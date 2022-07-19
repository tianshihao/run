#pragma once

#include <cstdint>
#include <iostream>
#include <string>

// Abstract product, For example, the vehicle.
class Product {
 public:
  Product() noexcept = default;
  Product(int id) noexcept : _id(id){};

  // And according to our real life, a thing or object can not be copied or
  // moved.
  Product(Product const&) = delete;
  Product& operator=(Product const&) = delete;

  Product(Product&&) = delete;
  Product& operator=(Product&&) = delete;

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
  Factory(Factory const&) = delete;
  Factory& operator=(Factory const&) = delete;

  Factory(Factory&&) = delete;
  Factory& operator=(Factory&&) = delete;

  virtual ~Factory() noexcept = default;

  // Note, despite its name, product creation is not the primary
  // responsibility of the creator. Usually, the creator class already
  // has some core business logic related to products. The factory
  // method helps to decouple this logic from the concrete prod-
  // uct classes. Here is an analogy: a large software development
  // company can have a training department for programmers.
  // However, the primary function of the company as a whole is
  // still writing code, not producing programmers.
  void Produce() {
    Product* product{GetProduct()};
    std::cout << product->ProductInfo();
  }

 private:
  virtual Product* GetProduct() = 0;
};

class FactoryA : public Factory {
 public:
  FactoryA() noexcept = default;
  ~FactoryA() noexcept override = default;

 private:
  Product* GetProduct() override { return new ProductA(_id++); }
  std::uint32_t static _id;
};

std::uint32_t FactoryA::_id{1};

class FactoryB : public Factory {
 public:
  FactoryB() noexcept = default;
  ~FactoryB() noexcept override = default;

 private:
  Product* GetProduct() override { return new ProductB(_id++); }
  std::uint32_t static _id;
};

std::uint32_t FactoryB::_id{1};
