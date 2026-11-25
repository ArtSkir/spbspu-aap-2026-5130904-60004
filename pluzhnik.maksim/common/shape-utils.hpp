#ifndef SHAPE_UTILS_HPP
#define SHAPE_UTILS_HPP

#include <cstddef>
#include "shape.hpp"

namespace pluzhnik
{
  void scaleFromPoint(Shape& shape, const point_t& center, double factor);
  double getTotalArea(const Shape* const* shapes, std::size_t count);
  rectangle_t getTotalFrameRect(const Shape* const* shapes, std::size_t count);
}

#endif
