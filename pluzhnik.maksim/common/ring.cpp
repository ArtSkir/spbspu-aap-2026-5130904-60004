#include "ring.hpp"
#include <stdexcept>

namespace
{
  constexpr double PI = 3.14159265358979323846;
  constexpr double DIAMETER_FACTOR = 2.0;
}

pluzhnik::Ring::Ring(double outer_r, double inner_r, const point_t& pos):
  outer_r_(outer_r),
  inner_r_(inner_r),
  pos_(pos)
{
  if (inner_r <= 0.0 || outer_r <= inner_r)
  {
    throw std::invalid_argument("Invalid ring radii");
  }
}

double pluzhnik::Ring::getArea() const
{
  return PI * (outer_r_ * outer_r_ - inner_r_ * inner_r_);
}

pluzhnik::rectangle_t pluzhnik::Ring::getFrameRect() const
{
  const double side = DIAMETER_FACTOR * outer_r_;
  return {side, side, pos_};
}

void pluzhnik::Ring::move(const point_t& pos)
{
  pos_ = pos;
}

void pluzhnik::Ring::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void pluzhnik::Ring::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  outer_r_ *= factor;
  inner_r_ *= factor;
}

pluzhnik::Shape* pluzhnik::Ring::clone() const
{
  return new Ring(*this);
}
