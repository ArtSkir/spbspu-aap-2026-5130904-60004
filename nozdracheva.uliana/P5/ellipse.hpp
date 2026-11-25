#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include "shape.hpp"

namespace nozdracheva
{
  class Ellipse: public Shape
  {
  private:
    double radius_x_;
    double radius_y_;
    point_t pos_;

  public:
    Ellipse(double radius_x, double radius_y, const point_t& pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

#endif
