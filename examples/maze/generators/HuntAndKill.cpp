#include "HuntAndKill.h"

#include "../../core/Random.h"

void HuntAndKill::Clear(World* world) {

}

Point2D HuntAndKill::getRandomPoint(World* world) {
	int sizeOver2 = world->GetSize() / 2;
	int x = Random::Range(0, sizeOver2);
	int y = Random::Range(0, sizeOver2);

	return Point2D(x, y);
}

std::vector<Point2D> HuntAndKill::getVisitableNeighbors(World* world) {
  std::vector<Point2D> neighbors;

  if (isVisitable(world, Point2D(current.x, current.y - 1))) {
    neighbors.emplace_back(Point2D(current.x, current.y - 1));
  }
  if (isVisitable(world, Point2D(current.x, current.y + 1))) {
    neighbors.emplace_back(Point2D(current.x, current.y + 1));
  }
  if (isVisitable(world, Point2D(current.x - 1, current.y))) {
    neighbors.emplace_back(Point2D(current.x - 1, current.y));
  }
  if (isVisitable(world, Point2D(current.x + 1, current.y))) {
    neighbors.emplace_back(Point2D(current.x + 1, current.y));
  }
}

bool HuntAndKill::isVisitable(World* world, Point2D point) {
  int sizeOver2 = world->GetSize() / 2;
  return abs(point.x) <= sizeOver2 && abs(point.y) <= sizeOver2 &&
         !visited[point.y][point.x] && world->GetNorth(point);
}

bool HuntAndKill::Step(World* world) {    
  std::vector<Point2D> neighbors = getVisitableNeighbors(world);
  if (neighbors.empty()) {
    return true;
  } else {
    int index = Random::Range(0, neighbors.size());
    Point2D next = neighbors[index];
    world->SetNodeColor(next, Color::Green);
  }
}