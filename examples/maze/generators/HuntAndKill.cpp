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

  return neighbors;
}

Point2D HuntAndKill::hunt(World* world) {
  Point2D result;
  int sizeOver2 = world->GetSize() / 2;
  for (int i = 0; i < sizeOver2; i++) {
    if (visited[i][sizeOver2 + 1]) {
      for (int j = 0; j < sizeOver2 - 1; j++) {
        if (visited[i][j + 1]) {
          result = Point2D(j + 1, i);
          world->SetNodeColor(result, Color::Green);
          return Point2D(i, j);
        }
      }
    }
  }
}

bool HuntAndKill::isVisitable(World* world, Point2D point) {
  int sizeOver2 = world->GetSize() / 2;
  return abs(point.x) <= sizeOver2 && abs(point.y) <= sizeOver2 &&
         !visited[point.y][point.x] && world->GetNorth(point);
}

bool HuntAndKill::Step(World* world) {    
  visited[current.y][current.x] = true;
  int sizeOver2 = world->GetSize() / 2;  
  if (!visited[current.y][sizeOver2 + 1]) {
    visited[current.y][sizeOver2 + 1] = true;
  }

  world->SetNodeColor(current, Color::Red.Dark());
    
  std::vector<Point2D> neighbors = getVisitableNeighbors(world);
  if (neighbors.empty()) {
    current = hunt(world);
    return true;
  } else {
    int index = Random::Range(0, neighbors.size());
    Point2D next = neighbors[index];
    world->SetNodeColor(next, Color::Green);
    
    Point2D delta = next - current;
    if (delta.y == -1) {
      world->SetNorth(current, false);
    } else if (delta.x == 1) {
      world->SetEast(current, false);
    } else if (delta.y == 1) {
      world->SetSouth(current, false);
    } else if (delta.x == -1) {
      world->SetWest(current, false);
    }

    current = next;

    return true;
  }
}