#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include "shape.hpp"

namespace pluzhnik
{
  class Ellipse: public Shape
  {
  public:
    Ellipse(double rx, double ry, const point_t& pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape* clone() const override;

  private:
    double rx_;
    double ry_;
    point_t pos_;
  };
}

#endif
