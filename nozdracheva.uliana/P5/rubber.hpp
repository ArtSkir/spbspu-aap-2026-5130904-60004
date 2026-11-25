#ifndef RUBBER_HPP
#define RUBBER_HPP
#include "shape.hpp"

namespace nozdracheva
{
  class Rubber: public Shape
  {
  private:
    double outer_radius_;
    double inner_radius_;
    point_t outer_center_;
    point_t inner_center_;

  public:
    Rubber(double outer_radius, double inner_radius, const point_t& outer_center, const point_t& inner_center);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}

#endif
