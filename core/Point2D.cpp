#include "Point2D.h"

#include <sstream>

bool Point2D::operator==(const Point2D& rhs) const {
    return y == rhs.y && x==rhs.x;
}

bool Point2D::operator!=(const Point2D& rhs) const {
  return x != rhs.x || y!=rhs.y;
}

Point2D& Point2D::operator=(const Point2D &rhs) {
  //Check for self-assignment
  if (this == &rhs)
    return *this;
  x = rhs.x;
  y = rhs.y;
  return *this;
}

std::string Point2D::toString() {
    std::stringstream output;

    output << "(" << x << ", " << y << ")";

    return output.str();
}
