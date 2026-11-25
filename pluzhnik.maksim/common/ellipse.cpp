#include "ellipse.hpp"
#include <stdexcept>

namespace
{
  constexpr double PI = 3.1415926;
  constexpr double DIAMETER_FACTOR = 2.0;
}

pluzhnik::Ellipse::Ellipse(double rx, double ry, const point_t& pos):
  rx_(rx),
  ry_(ry),
  pos_(pos)
{
  if (rx <= 0.0 || ry <= 0.0)
  {
    throw std::invalid_argument("Ellipse radii must be positive");
  }
}

double pluzhnik::Ellipse::getArea() const
{
  return PI * rx_ * ry_;
}

pluzhnik::rectangle_t pluzhnik::Ellipse::getFrameRect() const
{
  return {DIAMETER_FACTOR * rx_, DIAMETER_FACTOR * ry_, pos_};
}

void pluzhnik::Ellipse::move(const point_t& pos)
{
  pos_ = pos;
}

void pluzhnik::Ellipse::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void pluzhnik::Ellipse::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  rx_ *= factor;
  ry_ *= factor;
}

pluzhnik::Shape* pluzhnik::Ellipse::clone() const
{
  return new Ellipse(*this);
}
