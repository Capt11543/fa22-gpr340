#include "HuntAndKill.h"

#include <Random.h>

void HuntAndKill::Clear(World* world) {
    current = getRandomPoint(world);
    
    visited.clear();
    int sizeOver2 = world->GetSize() / 2;
    for (int i = -sizeOver2; i <= sizeOver2; i++) {
        for (int j = -sizeOver2; j <= sizeOver2 + 1; j++) {
            visited[i][j] = false;
        }
    }
}

Point2D HuntAndKill::getRandomNeighbor(World* world, Point2D point) {
  std::vector<Point2D> neighbors = getVisitableNeighbors(world, point); // get all visitable neighbors of that point
  if (neighbors.size() > 0) {  // if there are valid neighbors to visit...
    int roll = Random::Range(0, neighbors.size() - 1);
    return neighbors[roll];  // pick a random one
  }
  return Point2D(INT_MAX, INT_MAX); // return an impossibly large value if nothing is found
}

Point2D HuntAndKill::getRandomPoint(World* world) {
	int sizeOver2 = world->GetSize() / 2;
	int x = Random::Range(-sizeOver2, sizeOver2);
	int y = Random::Range(-sizeOver2, sizeOver2);

	return Point2D(x, y);
}

std::vector<Point2D> HuntAndKill::getVisitableNeighbors(World* world, Point2D point) {
  std::vector<Point2D> neighbors;
  int sizeOver2 = world->GetSize() / 2;

  // north
  if (abs(point.x) <= sizeOver2 && abs(point.y - 1) <= sizeOver2 && !visited[point.y - 1][point.x] && world->GetNorth(point)) {
    neighbors.emplace_back(Point2D(point.x, point.y - 1));
  }
  // east
  if (abs(point.x - 1) <= sizeOver2 && abs(point.y) <= sizeOver2 && !visited[point.y][point.x - 1] && world->GetEast(point)) {
    neighbors.emplace_back(Point2D(point.x - 1, point.y));
  }
  // south
  if (abs(point.x) <= sizeOver2 && abs(point.y + 1) <= sizeOver2 && !visited[point.y + 1][point.x] && world->GetSouth(point)) {
    neighbors.emplace_back(Point2D(point.x, point.y + 1));
  }
  // west
  if (abs(point.x - 1) <= sizeOver2 && abs(point.y) <= sizeOver2 && !visited[point.y][point.x +
      1] && world->GetWest(point)) {
    neighbors.emplace_back(Point2D(point.x + 1, point.y));
  }

  return neighbors;
}

Point2D HuntAndKill::hunt(World* world) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2 - 1; i++) { // loop through each row
    if (visited[i][sizeOver2 + 1]) { // if the current row has been visited...
      for (int j = -sizeOver2; j <= sizeOver2; j++) { // loop through all tiles in this row
        if (visited[i][j]) { // if the point has been visited...
          Point2D point(j, i);
          Point2D neighbor = getRandomNeighbor(world, point); // try to get a random neighbor of it
          if (abs(neighbor.x) <= sizeOver2 && abs(neighbor.y) <= sizeOver2) { // if it's valid...
            removeAdjascentWall(world, neighbor, point); // remove the wall between the neighbor and the current point in the for loop
            return neighbor; // return it
          }
        }
      }
    }
    if (visited[i + 1][sizeOver2 + 1]) { // if the next row has been visited...
      for (int j = -sizeOver2; j <= sizeOver2 - 1; j++) { // loop through all titles in the next row
        if (visited[i + 1][j]) { // if the point has been visited...
          Point2D point(j, i);
          Point2D neighbor = getRandomNeighbor(world, point);  // try to get a random neighbor of it
          if (abs(neighbor.x) <= sizeOver2 && abs(neighbor.y) <= sizeOver2) { // if it's valid...
            removeAdjascentWall(world, neighbor, point); // remove the wall between the neighbor and the current point in the for loop
            return neighbor; // return it
          }
        }
      }
    }
  }

  return Point2D(INT_MAX, INT_MAX); // return an impossibly large value if nothing is found
}

HuntAndKill::HuntAndKill(World* world) : current(getRandomPoint(world)) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    for (int j = -sizeOver2; j <= sizeOver2; j++) {
      visited[i][j] = false;
    }
  }
}

bool HuntAndKill::Step(World* world) {    
  visited[current.y][current.x] = true;
  int sizeOver2 = world->GetSize() / 2;  
  if (!visited[current.y][sizeOver2 + 1]) {
    visited[current.y][sizeOver2 + 1] = true; // mark this row as visited
  }

  world->SetNodeColor(current, Color::Red.Dark());
    
  std::vector<Point2D> neighbors = getVisitableNeighbors(world, current);
  if (neighbors.empty()) {
    Point2D huntedPoint = hunt(world);
    if (abs(huntedPoint.x) <= sizeOver2 && abs(huntedPoint.y) <= sizeOver2) {
      current = hunt(world);
      world->SetNodeColor(current, Color::Green);
      return true;
    }
  } else {
    int index = Random::Range(0, neighbors.size() - 1);
    Point2D next = neighbors[index];
    removeAdjascentWall(world, next, current);
    current = next;
    world->SetNodeColor(current, Color::Green);

    return true;
  }

  return false;
}

void HuntAndKill::removeAdjascentWall(World* world, Point2D next, Point2D previous) {
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
}