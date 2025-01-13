#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

// Forward declaration of visitor interface to avoid circular dependency
class Circle;
class Rectangle;

// 访问者接口
class Visitor {
 public:
  virtual void visit(Circle* c) = 0;
  virtual void visit(Rectangle* r) = 0;
};

// 元素接口
class Shape {
 public:
  virtual void accept(Visitor* visitor) = 0;
  virtual ~Shape() = default;  // 确保基类有虚析构函数
};

// 具体元素 - 圆形
class Circle : public Shape {
 public:
  Circle(double radius) : radius(radius) {}

  void accept(Visitor* visitor) override { visitor->visit(this); }

  double getRadius() const { return radius; }

 private:
  double radius;
};

// 具体元素 - 矩形
class Rectangle : public Shape {
 public:
  Rectangle(double width, double height) : width(width), height(height) {}

  void accept(Visitor* visitor) override { visitor->visit(this); }

  double getWidth() const { return width; }
  double getHeight() const { return height; }

 private:
  double width;
  double height;
};

// 具体访问者 - 计算面积
class AreaVisitor : public Visitor {
 public:
  void visit(Circle* c) override {
    double area = M_PI * std::pow(c->getRadius(), 2);
    std::cout << "Circle area: " << area << std::endl;
  }

  void visit(Rectangle* r) override {
    double area = r->getWidth() * r->getHeight();
    std::cout << "Rectangle area: " << area << std::endl;
  }
};

// 具体访问者 - 计算周长
class PerimeterVisitor : public Visitor {
 public:
  void visit(Circle* c) override {
    double perimeter = 2 * M_PI * c->getRadius();
    std::cout << "Circle perimeter: " << perimeter << std::endl;
  }

  void visit(Rectangle* r) override {
    double perimeter = 2 * (r->getWidth() + r->getHeight());
    std::cout << "Rectangle perimeter: " << perimeter << std::endl;
  }
};

int main() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Circle>(5));
  shapes.push_back(std::make_unique<Rectangle>(3, 7));

  AreaVisitor areaVisitor;
  PerimeterVisitor perimeterVisitor;

  for (const auto& shape : shapes) {
    shape->accept(&areaVisitor);
    shape->accept(&perimeterVisitor);
  }

  return 0;
}
