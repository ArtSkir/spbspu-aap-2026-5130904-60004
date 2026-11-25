#include "Diamond.hpp"
#include <stdexcept>

namespace
{
  const double HALF = 0.5;
}

namespace pechnikov
{
  Diamond::Diamond(double x, double y, point_t p):
    diag_x_(x),
    diag_y_(y),
    pos_(p)
  {
    if (diag_x_ <= 0.0 || diag_y_ <= 0.0)
    {
      throw std::invalid_argument("Diamond: Invalid len diagonali");
    }
  }

  double Diamond::getArea() const
  {
    return HALF * diag_x_ * diag_y_;
  }

  rectangle_t Diamond::getFrameRect() const
  {
    const double width = diag_x_;
    const double height = diag_y_;
    return {width, height, pos_};
  }

  void Diamond::move(const point_t& p)
  {
    pos_ = p;
  }

  void Diamond::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Diamond::scale(double k)
  {
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid koef");
    }
    diag_x_ *= k;
    diag_y_ *= k;
  }
}
