#include "rectangle.hpp"
#include <cmath>
#include <stdexcept>

nozdracheva::Rectangle::Rectangle(double width, double height, const point_t& pos):
  width_(width),
  height_(height),
  pos_(pos)
{
  if (!std::isfinite(width_) || !std::isfinite(height_) || !std::isfinite(pos_.x) || !std::isfinite(pos_.y)
      || width_ <= 0 || height_ <= 0)
  {
    throw std::invalid_argument("Invalid rectangle");
  }
}

double nozdracheva::Rectangle::getArea() const
{
  return width_ * height_;
}

nozdracheva::rectangle_t nozdracheva::Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void nozdracheva::Rectangle::move(const point_t& point)
{
  pos_ = point;
}

void nozdracheva::Rectangle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void nozdracheva::Rectangle::scale(double k)
{
  if (!std::isfinite(k) || k <= 0)
  {
    throw std::invalid_argument("Invalid scale");
  }
  width_ *= k;
  height_ *= k;
}
