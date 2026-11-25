#include "shape-utils.hpp"
#include <algorithm>
#include <stdexcept>

namespace
{
  constexpr double HALF_DIVISOR = 2.0;
}

void pluzhnik::scaleFromPoint(Shape& shape, const point_t& center, double factor)
{
  if (factor <= 0.0)
  {
    throw std::invalid_argument("Scale factor must be positive");
  }
  const rectangle_t frame = shape.getFrameRect();
  const double dx = frame.pos.x - center.x;
  const double dy = frame.pos.y - center.y;

  shape.move(center);
  shape.scale(factor);
  shape.move(dx * factor, dy * factor);
}

double pluzhnik::getTotalArea(const Shape* const* shapes, std::size_t count)
{
  double total = 0.0;
  for (std::size_t i = 0; i < count; ++i)
  {
    if (shapes[i] != nullptr)
    {
      total += shapes[i]->getArea();
    }
  }
  return total;
}

pluzhnik::rectangle_t pluzhnik::getTotalFrameRect(const Shape* const* shapes, std::size_t count)
{
  if (count == 0)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }

  bool initialized = false;
  double min_x = 0.0;
  double max_x = 0.0;
  double min_y = 0.0;
  double max_y = 0.0;

  for (std::size_t i = 0; i < count; ++i)
  {
    if (shapes[i] == nullptr)
    {
      continue;
    }
    const rectangle_t rect = shapes[i]->getFrameRect();
    const double half_w = rect.width / HALF_DIVISOR;
    const double half_h = rect.height / HALF_DIVISOR;
    const double left = rect.pos.x - half_w;
    const double right = rect.pos.x + half_w;
    const double bottom = rect.pos.y - half_h;
    const double top = rect.pos.y + half_h;

    if (!initialized)
    {
      min_x = left;
      max_x = right;
      min_y = bottom;
      max_y = top;
      initialized = true;
    }
    else
    {
      min_x = std::min(min_x, left);
      max_x = std::max(max_x, right);
      min_y = std::min(min_y, bottom);
      max_y = std::max(max_y, top);
    }
  }

  if (!initialized)
  {
    return {0.0, 0.0, {0.0, 0.0}};
  }

  const double width = max_x - min_x;
  const double height = max_y - min_y;
  const point_t center{min_x + width / HALF_DIVISOR, min_y + height / HALF_DIVISOR};
  return {width, height, center};
}
