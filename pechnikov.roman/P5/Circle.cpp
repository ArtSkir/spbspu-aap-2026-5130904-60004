#include "Circle.hpp"
#include <stdexcept>

namespace
{
  const double PI = 3.14159265358979323846;
  const double TWO = 2.0;
}

namespace pechnikov
{
  Circle::Circle(double r, point_t p):
    radius_(r),
    pos_(p)
  {
    if (r <= 0.0)
    {
      throw std::invalid_argument("Circle: invalid radius");
    }
  }

  double Circle::getArea() const
  {
    return PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    const double width = TWO * radius_;
    const double height = TWO * radius_;
    return {width, height, pos_};
  }

  void Circle::move(const point_t& p)
  {
    pos_ = p;
  }

  void Circle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Circle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid koef");
    }
    radius_ *= k;
  }
}
