#include "rectangle.hpp"
#include "rubber.hpp"
#include "ellipse.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

void printRect(const nozdracheva::rectangle_t& rect)
{
  std::cout << "center: (" << rect.pos.x << ", " << rect.pos.y << ")"
            << ", width: " << rect.width << ", height: " << rect.height << "\n";
}

void printShapes(nozdracheva::Shape* shapes[], int count)
{
  double total_area = 0;
  nozdracheva::rectangle_t rect = shapes[0]->getFrameRect();
  double left = rect.pos.x - rect.width / 2;
  double right = rect.pos.x + rect.width / 2;
  double bottom = rect.pos.y - rect.height / 2;
  double top = rect.pos.y + rect.height / 2;

  for (int i = 0; i < count; ++i)
  {
    std::cout << "Shape " << i + 1 << ":\n";
    const double area = shapes[i]->getArea();
    std::cout << "Area: " << area << "\n";
    rect = shapes[i]->getFrameRect();
    std::cout << "Frame: ";
    printRect(rect);
    total_area += area;

    const double x1 = rect.pos.x - rect.width / 2;
    const double x2 = rect.pos.x + rect.width / 2;
    const double y1 = rect.pos.y - rect.height / 2;
    const double y2 = rect.pos.y + rect.height / 2;

    if (x1 < left)
    {
      left = x1;
    }
    if (x2 > right)
    {
      right = x2;
    }
    if (y1 < bottom)
    {
      bottom = y1;
    }
    if (y2 > top)
    {
      top = y2;
    }
  }

  if (!std::isfinite(total_area) || total_area <= 0 || !std::isfinite(right - left) || !std::isfinite(top - bottom))
  {
    throw std::invalid_argument("Invalid scaling result");
  }

  std::cout << "Total area: " << total_area << "\n";
  std::cout << "Total frame: ";
  printRect({right - left, top - bottom, {(left + right) / 2, (bottom + top) / 2}});
}

void scaleShapes(nozdracheva::Shape* shapes[], int count, const nozdracheva::point_t& point, double k)
{
  for (int i = 0; i < count; ++i)
  {
    const nozdracheva::rectangle_t before = shapes[i]->getFrameRect();
    shapes[i]->move(point);
    const nozdracheva::rectangle_t at_point = shapes[i]->getFrameRect();
    const double center_x = before.pos.x - (at_point.pos.x - point.x);
    const double center_y = before.pos.y - (at_point.pos.y - point.y);
    shapes[i]->move({center_x, center_y});
    shapes[i]->scale(k);
    shapes[i]->move((center_x - point.x) * (k - 1), (center_y - point.y) * (k - 1));

    const nozdracheva::rectangle_t after = shapes[i]->getFrameRect();
    const double area = shapes[i]->getArea();
    if (!std::isfinite(area) || area <= 0 || !std::isfinite(after.width) || !std::isfinite(after.height)
        || !std::isfinite(after.pos.x) || !std::isfinite(after.pos.y) || after.width <= 0 || after.height <= 0)
    {
      throw std::invalid_argument("Invalid scaling result");
    }
  }
}

int main()
{
  try
  {
    const double rect_width = 4.0;
    const double rect_height = 2.0;
    const nozdracheva::point_t rect_pos = {1.0, 1.0};

    const double outer_radius = 5.0;
    const double inner_radius = 2.0;
    const nozdracheva::point_t outer_center = {8.0, 3.0};
    const nozdracheva::point_t inner_center = {9.0, 3.0};

    const double radius_x = 3.0;
    const double radius_y = 1.5;
    const nozdracheva::point_t ellipse_pos = {-4.0, 2.0};

    nozdracheva::Rectangle rectangle(rect_width, rect_height, rect_pos);
    nozdracheva::Rubber rubber(outer_radius, inner_radius, outer_center, inner_center);
    nozdracheva::Ellipse ellipse(radius_x, radius_y, ellipse_pos);
    nozdracheva::Shape* shapes[] = {&rectangle, &rubber, &ellipse};
    const int count = 3;

    std::cout << "Before scaling:\n";
    printShapes(shapes, count);

    nozdracheva::point_t point = {};
    double k = 0;
    std::cout << "Enter x, y and scale: ";
    if (!(std::cin >> point.x >> point.y >> k) || !std::isfinite(point.x) || !std::isfinite(point.y)
        || !std::isfinite(k) || k <= 0)
    {
      std::cerr << "Invalid scaling parameters\n";
      return 1;
    }

    scaleShapes(shapes, count, point, k);
    std::cout << "After scaling:\n";
    printShapes(shapes, count);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
