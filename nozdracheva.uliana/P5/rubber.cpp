#include "rubber.hpp"
#include <cmath>
#include <stdexcept>

nozdracheva::Rubber::Rubber(
    double outer_radius, double inner_radius, const point_t& outer_center, const point_t& inner_center):
  outer_radius_(outer_radius),
  inner_radius_(inner_radius),
  outer_center_(outer_center),
  inner_center_(inner_center)
{
  const double dx = outer_center_.x - inner_center_.x;
  const double dy = outer_center_.y - inner_center_.y;
  const double distance = std::hypot(dx, dy);

  if (!std::isfinite(outer_radius_) || !std::isfinite(inner_radius_) || !std::isfinite(outer_center_.x)
      || !std::isfinite(outer_center_.y) || !std::isfinite(inner_center_.x) || !std::isfinite(inner_center_.y)
      || outer_radius_ <= 0 || inner_radius_ <= 0 || distance <= 0 || distance + inner_radius_ >= outer_radius_)
  {
    throw std::invalid_argument("Invalid rubber");
  }
}

double nozdracheva::Rubber::getArea() const
{
  const double pi = std::acos(-1.0);
  return pi * (outer_radius_ * outer_radius_ - inner_radius_ * inner_radius_);
}

nozdracheva::rectangle_t nozdracheva::Rubber::getFrameRect() const
{
  return {2 * outer_radius_, 2 * outer_radius_, outer_center_};
}

void nozdracheva::Rubber::move(const point_t& point)
{
  move(point.x - inner_center_.x, point.y - inner_center_.y);
}

void nozdracheva::Rubber::move(double dx, double dy)
{
  outer_center_.x += dx;
  outer_center_.y += dy;
  inner_center_.x += dx;
  inner_center_.y += dy;
}

void nozdracheva::Rubber::scale(double k)
{
  if (!std::isfinite(k) || k <= 0)
  {
    throw std::invalid_argument("Invalid scale");
  }
  outer_center_.x = inner_center_.x + (outer_center_.x - inner_center_.x) * k;
  outer_center_.y = inner_center_.y + (outer_center_.y - inner_center_.y) * k;
  outer_radius_ *= k;
  inner_radius_ *= k;
}
