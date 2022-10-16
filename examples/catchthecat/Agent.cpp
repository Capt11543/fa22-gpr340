#include "Agent.h"
#include "World.h"

#include <iostream>

bool Agent::isExit(World* world, Point2D point) {
    std::cout << "Checking if " << abs(point.x) << " == " << world->getWorldSideSize() / 2 << " || " << abs(point.y) << " == " << world->getWorldSideSize() / 2 << std::endl;

    bool result = abs(point.x) == world->getWorldSideSize() / 2 || abs(point.y) == world->getWorldSideSize() / 2;

    std::cout << "Result is: " << (result ? "true" : "false") << std::endl;
    return result;
}

bool QueueEntry::operator==(const Point2D& rhs) const {
    return position.x == rhs.x && position.y == rhs.y;
}

std::string QueueEntry::toString() {
  std::stringstream output;

  output << position.toString() << " weight: " << weight;

  return output.str();
}