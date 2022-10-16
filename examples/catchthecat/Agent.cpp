#include "Agent.h"
#include "World.h"

bool Agent::isExit(World* world, Point2D point) {
    return abs(point.x) == world->getWorldSideSize() / 2 || abs(point.y) == world->getWorldSideSize() / 2;
}

bool QueueEntry::operator==(const Point2D& rhs) const {
    return position.x == rhs.x && position.y == rhs.y;
}

std::vector<Point2D> Agent::makePath(World* world, Point2D origin) {
  std::map<int, std::map<int, bool>> visited;
  std::map<int, std::map<int, Point2D>> cameFrom;

  Point2D endPoint = Point2D();
  std::vector<QueueEntry> queue;
  queue.push_back(QueueEntry(origin, 0));

  while (!queue.empty()) {
    QueueEntry head = queue[0];
    queue.erase(queue.begin());

    // mark the head as visited
    visited[head.position.x][head.position.y] = true;

    // check if the head is an exit
    if (isExit(world, head.position)) {
      endPoint = head.position;
      break;
    }

    // for each neighbor
    std::vector<Point2D> neighbors = world->getNeighbors(head.position);
    for (Point2D neighbor : neighbors) {
      if (abs(neighbor.x) > world->getWorldSideSize() / 2 ||
          abs(neighbor.y) > world->getWorldSideSize() / 2) {
        continue;
      }

      // don't add if it is already visited
      if (visited[neighbor.x][neighbor.y]) {
        continue;
      }

      // don't add if it is already in the queue
      if (std::find(queue.begin(), queue.end(), neighbor) != queue.end()) {
        continue;
      }

      // don't add if it is blocked
      if (world->getContent(neighbor)) {
        continue;
      }

      // add neighbor to queue
      queue.push_back({neighbor, head.weight + 1});

      // mark the neighbor as having come from the head
      cameFrom[neighbor.x][neighbor.y] = head.position;
    }

    // write win condition (path found condition) and navigation process here
    // if the absolute value of the x or the y is equal to world.sideSize / 2;
  }

  // Build path
  std::vector<Point2D> path;
  Point2D head = endPoint;

  while (head != origin) {
    path.insert(path.begin(), head);
    head = cameFrom[head.x][head.y];
  }

  return path;
}