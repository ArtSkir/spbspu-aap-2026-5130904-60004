#include "ellipse.hpp"
#include <cmath>
#include <stdexcept>

nozdracheva::Ellipse::Ellipse(double radius_x, double radius_y, const point_t& pos):
  radius_x_(radius_x),
  radius_y_(radius_y),
  pos_(pos)
{
  if (!std::isfinite(radius_x_) || !std::isfinite(radius_y_) || !std::isfinite(pos_.x) || !std::isfinite(pos_.y)
      || radius_x_ <= 0 || radius_y_ <= 0)
  {
    throw std::invalid_argument("Invalid ellipse");
  }
}

double nozdracheva::Ellipse::getArea() const
{
  const double pi = std::acos(-1.0);
  return pi * radius_x_ * radius_y_;
}

nozdracheva::rectangle_t nozdracheva::Ellipse::getFrameRect() const
{
  return {2 * radius_x_, 2 * radius_y_, pos_};
}

void nozdracheva::Ellipse::move(const point_t& point)
{
  pos_ = point;
}

void nozdracheva::Ellipse::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void nozdracheva::Ellipse::scale(double k)
{
  if (!std::isfinite(k) || k <= 0)
  {
    throw std::invalid_argument("Invalid scale");
  }
  radius_x_ *= k;
  radius_y_ *= k;
}
