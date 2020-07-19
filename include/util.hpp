#ifndef MATSE_MCT_UTIL_HPP
#define MATSE_MCT_UTIL_HPP

#include "Data.hpp"

namespace MATSE::MCT {

double transform(double min1, double max1, double min2, double max2, double x1);

/**
 * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *
 * integer incremental error version
 */
void drawLine(Point from, Point to, auto plot) {
  // cast uint8_t to int
  int x0 = from.x;
  int y0 = from.y;
  int x1 = to.x;
  int y1 = to.y;

  auto dx = std::abs(x1 - x0);
  auto sx = x0 < x1 ? 1 : -1;
  auto dy = -std::abs(y1 - y0);
  auto sy = y0 < y1 ? 1 : -1;
  auto err = dx + dy;
  while (true) {
    plot(Point{(uint8_t)x0, (uint8_t)y0});
    if (x0 == x1 && y0 == y1) {
      break;
    }
    auto e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void drawFrame(Point upperLeft, Point lowerRight, auto plot) {
  drawLine({upperLeft.x, upperLeft.y}, {lowerRight.x, upperLeft.y}, plot);
  drawLine({upperLeft.x, lowerRight.y}, {lowerRight.x, lowerRight.y}, plot);
  drawLine({upperLeft.x, upperLeft.y}, {upperLeft.x, lowerRight.y}, plot);
  drawLine({lowerRight.x, upperLeft.y}, {lowerRight.x, lowerRight.y}, plot);
}

} // namespace MATSE::MCT

#endif