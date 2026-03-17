#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Shape {
 public:
  explicit Shape(std::string name) : name_(std::move(name)) {}
  virtual ~Shape() = default;

  const std::string& name() const {
    return name_;
  }

  virtual double area() const = 0;

 private:
  std::string name_;
};

class Rectangle final : public Shape {
 public:
  Rectangle(double width, double height)
      : Shape("Rectangle"), width_(width), height_(height) {}

  double area() const override {
    return width_ * height_;
  }

 private:
  double width_;
  double height_;
};

class Circle final : public Shape {
 public:
  explicit Circle(double radius) : Shape("Circle"), radius_(radius) {}

  double area() const override {
    return 3.141592653589793 * radius_ * radius_;
  }

 private:
  double radius_;
};

int main() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.emplace_back(std::make_unique<Rectangle>(4.0, 5.0));
  shapes.emplace_back(std::make_unique<Circle>(3.0));

  for (const auto& shape : shapes) {
    std::cout << shape->name() << " area: " << shape->area() << '\n';
  }

  return 0;
}
