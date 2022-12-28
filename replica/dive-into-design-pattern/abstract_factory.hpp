#pragma once
/**
 * @brief A set of factory methods.
 *
 */

#include <algorithm>
#include <memory>

class Chair;
class Sofa;
class CoffeeTable;

class AbstractFurnitureFactory {
 public:
  virtual ~AbstractFurnitureFactory() = default;
  virtual std::unique_ptr<Chair> CreateChair() = 0;
  virtual std::unique_ptr<Sofa> CreateSofa() = 0;
  virtual std::unique_ptr<CoffeeTable> CreateCoffeeTable() = 0;
};

class VictorianFurnitureFactory : public AbstractFurnitureFactory {
 public:
  std::unique_ptr<Chair> CreateChair() override;
  std::unique_ptr<Sofa> CreateSofa() override;
  std::unique_ptr<CoffeeTable> CreateCoffeeTable() override;
};

class ModernFurnitureFactory : public AbstractFurnitureFactory {
 public:
  std::unique_ptr<Chair> CreateChair() override;
  std::unique_ptr<Sofa> CreateSofa() override;
  std::unique_ptr<CoffeeTable> CreateCoffeeTable() override;
};

class ArtDecoFurnitureFactory : public AbstractFurnitureFactory {
 public:
  std::unique_ptr<Chair> CreateChair() override;
  std::unique_ptr<Sofa> CreateSofa() override;
  std::unique_ptr<CoffeeTable> CreateCoffeeTable() override;
};

class Chair {
 public:
  virtual ~Chair() = default;
  virtual void SitOn() = 0;
};

class VictorianChair : public Chair {
 public:
  void SitOn() override;
};

class ModernChair : public Chair {
 public:
  void SitOn() override;
};

class ArtDecoChair : public Chair {
 public:
  void SitOn() override;
};

class Sofa {
 public:
  virtual ~Sofa() = default;
  virtual void LieOn() = 0;
};

class VictorianSofa : public Sofa {
 public:
  void LieOn() override;
};

class ModernSofa : public Sofa {
 public:
  void LieOn() override;
};

class ArtDecoSofa : public Sofa {
 public:
  void LieOn() override;
};

class CoffeeTable {
 public:
  virtual ~CoffeeTable() = default;
  virtual void PutOn() = 0;
};

class VictorianCoffeeTable : public CoffeeTable {
 public:
  void PutOn() override;
};

class ModernCoffeeTable : public CoffeeTable {
 public:
  void PutOn() override;
};

class ArtDecoCoffeeTable : public CoffeeTable {
 public:
  void PutOn() override;
};