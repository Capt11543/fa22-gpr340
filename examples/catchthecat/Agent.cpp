#include "Agent.h"
#include "World.h"

bool Agent::isExit(World* world, Point2D point) {
    return abs(point.x) == world->getWorldSideSize() / 2 || abs(point.y) == world->getWorldSideSize() / 2;
}

bool QueueEntry::operator==(const Point2D& rhs) const {
    return position.x == rhs.x && position.y == rhs.y;
}