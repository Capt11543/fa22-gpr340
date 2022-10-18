#include "Agent.h"
#include "World.h"

bool QueueEntry::operator==(const Point2D& rhs) const {
    return position.x == rhs.x && position.y == rhs.y;
}