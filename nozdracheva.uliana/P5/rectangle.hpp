#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace nozdracheva
{
  class Rectangle: public Shape
  {
  private:
    double width_;
    double height_;
    point_t pos_;

  public:
    Rectangle(double width, double height, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

#endif
