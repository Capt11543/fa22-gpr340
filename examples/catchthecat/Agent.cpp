#include "Agent.h"
#include "World.h"

bool Agent::isExit(World* world, Point2D point) {
  return abs(point.x) == world->getWorldSideSize() / 2 ||
         abs(point.y) == world->getWorldSideSize() / 2; // fucking hate the formatting here, how do I change it?
}