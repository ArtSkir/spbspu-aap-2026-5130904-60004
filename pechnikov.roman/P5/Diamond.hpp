#ifndef DIAMOND_HPP
#define DIAMOND_HPP

#include "shape.hpp"

namespace pechnikov
{
  class Diamond: public Shape
  {
  private:
    double diag_x_;
    double diag_y_;
    point_t pos_;

  public:
    Diamond(double x, double y, point_t p);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

#endif
