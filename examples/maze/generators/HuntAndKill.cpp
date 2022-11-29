#include "HuntAndKill.h"

#include <Random.h>

bool HuntAndKill::allColumnsVisited(World* world, int rowNumber) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    if (!visited[rowNumber][i]) {
      return false;
    }
  }
  return true;
}

void HuntAndKill::Clear(World* world) {
  int sizeOver2 = world->GetSize() / 2;

  current = Point2D(-sizeOver2, -sizeOver2);
  state = State::DIVING;

  visited.clear();
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    for (int j = -sizeOver2; j <= sizeOver2; j++) {
      visited[i][j] = false;
    }
  }

  rowVisited.clear();
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    rowVisited[i] = false;
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
    auto sideOver2 = world->GetSize() / 2;
    std::vector<Point2D> visitables;

    // north
    if ((abs(point.x) <= sideOver2 && abs(point.y - 1) <= sideOver2) && // should be inside the board
        !visited[point.y - 1][point.x] && // not visited yet
        world->GetNorth(point)) // has wall
        visitables.emplace_back(point.x, point.y - 1);
    // east
    if ((abs(point.x + 1) <= sideOver2 && abs(point.y) <= sideOver2) && // should be inside the board
        !visited[point.y][point.x + 1] && // not visited yet
        world->GetEast(point)) // has wall
        visitables.emplace_back(point.x + 1, point.y);
    // south
    if ((abs(point.x) <= sideOver2 && abs(point.y + 1) <= sideOver2) && // should be inside the board
        !visited[point.y + 1][point.x] && // not visited yet
        world->GetSouth(point)) // has wall
        visitables.emplace_back(point.x, point.y + 1);
    // west
    if ((abs(point.x - 1) <= sideOver2 && abs(point.y) <= sideOver2) && // should be inside the board
        !visited[point.y][point.x - 1] && // not visited yet
        world->GetWest(point)) // has wall
        visitables.emplace_back(point.x - 1, point.y);

    return visitables;
}

HuntAndKill::HuntAndKill(World* world) {
    Clear(world);
}

bool HuntAndKill::Step(World* world) {
  int sizeOver2 = world->GetSize() / 2;

  if (state == State::DIVING) {
    visited[current.y][current.x] = true;
    if (!rowVisited[current.y]) {
      rowVisited[current.y] = true;  // mark this row as visited
    }

    world->SetNodeColor(current, Color::Red.Dark());

    std::vector<Point2D> neighbors = getVisitableNeighbors(world, current);
    if (neighbors.empty()) {
      state = State::HUNTING_ROWS;
      for (int i = -sizeOver2; i <= sizeOver2; i++) {
        for (int j = -sizeOver2; j <= sizeOver2; j++) {
          if (visited[i][j]) {
            world->SetNodeColor(Point2D(j, i), Color::Black);
          }
        }
      }
      current = Point2D(-sizeOver2, -sizeOver2);
      setRowColor(world, current.y, Color::Yellow);

      return true;
    } else {
      int index = Random::Range(0, neighbors.size() - 1);
      Point2D next = neighbors[index];
      removeAdjascentWall(world, next, current);
      current = next;
      world->SetNodeColor(current, Color::Green);

      return true;
    }
  }
  if (state == State::HUNTING_ROWS) {
    // somewhere in here I should check if ALL columns have been visited within this row; if so, move on to the next row
    if (rowVisited[current.y]) {
      if (allColumnsVisited(world, current.y)) {
        revertRowColor(world, current.y);
        current = Point2D(current.x, current.y + 1);
        setRowColor(world, current.y, Color::Yellow);

        return true;
      } else {
        state = State::HUNTING_COLUMNS;
        revertRowColor(world, current.y);
        world->SetNodeColor(current, Color::Yellow);

        return true;
      }
    } else {
      revertRowColor(world, current.y);
      current = Point2D(current.x, current.y + 1);
      setRowColor(world, current.y, Color::Yellow);

      return true;
    }
  }
  if (state == State::HUNTING_COLUMNS) {
    if (visited[current.y][current.x]) {
      Point2D neighbor = getRandomNeighbor(world, current);
      if (abs(neighbor.x) <= sizeOver2 && abs(neighbor.y) <= sizeOver2) {
        state = State::DIVING;
        removeAdjascentWall(world, neighbor, current);
        revertColor(world, current);
        current = neighbor;
        world->SetNodeColor(current, Color::Green);

        return true;
      } else {
        revertColor(world, current);
        current = Point2D(current.x + 1, current.y);
        world->SetNodeColor(current, Color::Yellow);

        return true;
      }
    } else {
      revertColor(world, current);
      current = Point2D(current.x + 1, current.y);
      world->SetNodeColor(current, Color::Yellow);

      return true;
    }
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

void HuntAndKill::revertColor(World* world, Point2D point) {
  if (visited[point.y][point.x]) {
    world->SetNodeColor(point, Color::Black);
  } else {
    world->SetNodeColor(point, Color::LightGray);
  }
}

void HuntAndKill::revertRowColor(World* world, int rowNumber) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    revertColor(world, Point2D(i, rowNumber));
  }
}

void HuntAndKill::setRowColor(World* world, int rowNumber, const Color32& color) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    world->SetNodeColor(Point2D(i, rowNumber), color);
  }
}