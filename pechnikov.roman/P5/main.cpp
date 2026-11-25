#include <iostream>
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Diamond.hpp"

namespace
{
  const double HALF = 0.5;
  const double TWO = 2.0;
}

namespace pechnikov
{
  void printinf(Shape* const* shapes, int n)
  {
    if (n <= 0)
    {
      return;
    }
    const rectangle_t first_frame = shapes[0]->getFrameRect();

    double xmin = first_frame.pos.x - first_frame.width * HALF;
    double xmax = first_frame.pos.x + first_frame.width * HALF;
    double ymin = first_frame.pos.y - first_frame.height * HALF;
    double ymax = first_frame.pos.y + first_frame.height * HALF;

    double sum_area = 0.0;
    for (int i = 0; i < n; i++)
    {
      std::cout << "Shape #" << i + 1 << "\n";
      std::cout << "Area: " << shapes[i]->getArea() << "\n";
      sum_area += shapes[i]->getArea();
      const rectangle_t frame = shapes[i]->getFrameRect();
      std::cout << "Frame: width " << frame.width;
      std::cout << ", height " << frame.height;
      std::cout << ", pos(" << frame.pos.x << ", " << frame.pos.y << ")\n";

      const double left = frame.pos.x - frame.width * HALF;
      const double right = frame.pos.x + frame.width * HALF;
      const double bottom = frame.pos.y - frame.height * HALF;
      const double top = frame.pos.y + frame.height * HALF;

      if (left < xmin)
      {
        xmin = left;
      }
      if (right > xmax)
      {
        xmax = right;
      }
      if (bottom < ymin)
      {
        ymin = bottom;
      }
      if (top > ymax)
      {
        ymax = top;
      }
    }
    std::cout << "Summary Area: " << sum_area << "\n";
    std::cout << "all width = " << xmax - xmin << ", all height = " << ymax - ymin;
    std::cout << ", all pos(" << (xmax + xmin) * HALF << ", " << (ymax + ymin) * HALF << ")\n";
  }

  void niceshape(Shape* shape, point_t tochka, double k)
  {
    const rectangle_t rec = shape->getFrameRect();
    const point_t oldpos = rec.pos;
    const double dx = tochka.x - oldpos.x;
    const double dy = tochka.y - oldpos.y;

    shape->scale(k);

    shape->move({oldpos.x + dx - k * dx, oldpos.y + dy - k * dy});
  }

  void niceshapes(Shape* const* shapes, point_t tochka, double k, int n)
  {
    for (int i = 0; i < n; i++)
    {
      niceshape(shapes[i], tochka, k);
    }
  }
}

int main()
{
  const double a1 = 3.1, b1 = 5.0, x1 = 0.0, y1 = 0.0;
  const double d1 = 10.0, d2 = 7.0, x2 = 1.0, y2 = 6.0;
  const double rad = 13.0, x3 = 5.0, y3 = 6.0;
  const int n = 3;
  pechnikov::Shape* shapes[n] = {};
  try
  {
    shapes[0] = new pechnikov::Rectangle{a1, b1, {x1, y1}};
    shapes[1] = new pechnikov::Diamond{d1, d2, {x2, y2}};
    shapes[2] = new pechnikov::Circle{rad, {x3, y3}};

    pechnikov::printinf(shapes, n);

    double cx = 0.0, cy = 0.0, k = 0.0;
    if (!(std::cin >> cx >> cy >> k))
    {
      throw std::invalid_argument("incorrect argument");
    }
    if (k <= 0.0)
    {
      throw std::invalid_argument("Invalid koef");
    }
    const pechnikov::point_t tochka{cx, cy};
    pechnikov::niceshapes(shapes, tochka, k, n);
    pechnikov::printinf(shapes, n);
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << "\n";
    for (int i = 0; i < n; i++)
    {
      delete shapes[i];
    }
    return 1;
  }
  for (int i = 0; i < n; i++)
  {
    delete shapes[i];
  }
  return 0;
}
