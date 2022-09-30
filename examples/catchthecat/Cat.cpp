#include <algorithm>
#include "Cat.h"
#include <stdexcept>
#include <vector>
#include "World.h"

Point2D Cat::Move(World* world) {
  Point2D cat = world->getCat();
  std::map<int, std::map<int, bool>> visited;
  std::vector<QueueEntry> queue;
  queue.push_back({cat, 0});

  while (!queue.empty()) {
    QueueEntry head = queue[0];
    queue.erase(queue.begin());

    // mark the head as visited
    visited[head.position.x][head.position.y] = true;
    // for each neighbor

    // std::vector<Point2D> neighbors = world->getNeighbors(visited[head.position.x][head.position.y]);
    // - check if is not visited yet
    // - check if is not in the queue
    // - check if it can be visited
    // - add to the queue, adding the weight
    // - mark the neighbor as having come from the head

    // write win condition and navigation process here
    // if the absolute value of the x or the y is equal to world.sideSize / 2;
  }

  auto rand = Random::Range(0,5);
  auto pos = world->getCat();
  switch(rand){
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
