#include "Rectangle.hpp"
#include <stdexcept>

namespace pechnikov
{
  Rectangle::Rectangle(double w, double h, point_t p):
    width_(w),
    height_(h),
    pos_(p)
  {
    if (w <= 0.0 || h <= 0.0)
    {
      throw std::invalid_argument("Rectangle: sides must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return {width_, height_, pos_};
  }

  void Rectangle::move(const point_t& p)
  {
    pos_ = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid koef");
    }
    width_ *= k;
    height_ *= k;
  }
}
