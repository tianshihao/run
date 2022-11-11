#pragma once

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

  // Some business.
  void Produce() {
    Product* product{GetProduct()};
    std::cout << product->ProductInfo();
  }

 private:
  virtual Product* GetProduct(int id = 0) = 0;
};

class FactoryA : public Factory {
 public:
  FactoryA() noexcept = default;
  ~FactoryA() noexcept override = default;

  Product* GetProduct(int id = 0) override { return new ProductA(id); }
};

class FactoryB : public Factory {
 public:
  FactoryB() noexcept = default;
  ~FactoryB() noexcept override = default;

  Product* GetProduct(int id = 0) override { return new ProductB(id); }
};
