#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace pluzhnik
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& pos);
    Rectangle(const rectangle_t& rect);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape* clone() const override;

  private:
    rectangle_t rect_;
  };
}

#endif
