#include "rectangle.hpp"
#include <stdexcept>

pluzhnik::Rectangle::Rectangle(double width, double height, const point_t& pos):
  rect_{width, height, pos}
{
  if (width <= 0.0 || height <= 0.0)
  {
    throw std::invalid_argument("Rectangle dimensions must be positive");
  }
}

pluzhnik::Rectangle::Rectangle(const rectangle_t& rect):
  Rectangle(rect.width, rect.height, rect.pos)
{}

double pluzhnik::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

pluzhnik::rectangle_t pluzhnik::Rectangle::getFrameRect() const
{
  return rect_;
}

void pluzhnik::Rectangle::move(const point_t& pos)
{
  rect_.pos = pos;
}

void pluzhnik::Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void pluzhnik::Rectangle::scale(double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  rect_.width *= factor;
  rect_.height *= factor;
}

pluzhnik::Shape* pluzhnik::Rectangle::clone() const
{
  return new Rectangle(*this);
}
