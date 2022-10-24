#include "circle.hpp"

#include <cmath>
void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  const double sum = radius + otherCircle.radius;
  double smallerRds;
  double largerRds;
  if (radius >= otherCircle.radius) {
    smallerRds = otherCircle.radius;
    largerRds = radius;
  }
  else {
    largerRds = otherCircle.radius;
    smallerRds = radius;
  }
  const double sub = largerRds - smallerRds;
  const double distance = center.distanceFrom(otherCircle.center);

  if (distance >= sum) {
    return 0.0;
  }
  else if (distance <= sub) {
    return M_PI * smallerRds * smallerRds;
  }
  else {
    double a = std::acos(
        (smallerRds * smallerRds + distance * distance - largerRds * largerRds) /
        (2.0 * smallerRds * distance));
    double b = std::acos(
        (largerRds * largerRds + distance * distance - smallerRds * smallerRds) /
        (2.0 * largerRds * distance));
    return a * smallerRds * smallerRds + b * largerRds * largerRds -
           smallerRds * distance * std::sin(a);
  }
}
