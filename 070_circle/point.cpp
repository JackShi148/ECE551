#include "point.hpp"

#include <cmath>
#include <cstdio>
#include <cstdlib>

using std ::sqrt;

void Point ::move(double dx, double dy) {
  x += dx;
  y += dy;
}

double Point ::distanceFrom(const Point & p) {
  double dist = 0;
  dist = sqrt(pow((x - p.x), 2) + pow((y - p.y), 2));
  return dist;
}
