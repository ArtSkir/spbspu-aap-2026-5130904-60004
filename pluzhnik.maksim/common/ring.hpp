#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

namespace pluzhnik
{
  class Ring: public Shape
  {
  public:
    Ring(double outer_r, double inner_r, const point_t& pos);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    Shape* clone() const override;

  private:
    double outer_r_;
    double inner_r_;
    point_t pos_;
  };
}

#endif
