#include "HuntAndKill.h"

#include <Random.h>

void HuntAndKill::Clear(World* world) {
    int sizeOver2 = world->GetSize() / 2;
    
    current = Point2D(-sizeOver2, -sizeOver2);
    state = NORMAL;
    visited.clear();

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

std::vector<Point2D> HuntAndKill::getVisitableNeighbors(World* w, Point2D p) {
    auto sideOver2 = w->GetSize() / 2;
    std::vector<Point2D> visitables;

    // north
    if ((abs(p.x) <= sideOver2 && abs(p.y - 1) <= sideOver2) && // should be inside the board
        !visited[p.y - 1][p.x] && // not visited yet
        w->GetNorth(p)) // has wall
        visitables.emplace_back(p.x, p.y - 1);
    // east
    if ((abs(p.x + 1) <= sideOver2 && abs(p.y) <= sideOver2) && // should be inside the board
        !visited[p.y][p.x + 1] && // not visited yet
        w->GetEast(p)) // has wall
        visitables.emplace_back(p.x + 1, p.y);
    // south
    if ((abs(p.x) <= sideOver2 && abs(p.y + 1) <= sideOver2) && // should be inside the board
        !visited[p.y + 1][p.x] && // not visited yet
        w->GetSouth(p)) // has wall
        visitables.emplace_back(p.x, p.y + 1);
    // west
    if ((abs(p.x - 1) <= sideOver2 && abs(p.y) <= sideOver2) && // should be inside the board
        !visited[p.y][p.x - 1] && // not visited yet
        w->GetWest(p)) // has wall
        visitables.emplace_back(p.x - 1, p.y);

    return visitables;
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

HuntAndKill::HuntAndKill(World* world) {
    Clear(world);
}

bool HuntAndKill::Step(World* world) {
    int sizeOver2 = world->GetSize() / 2;

    if (state == NORMAL) {
        visited[current.y][current.x] = true;
        if (!visited[current.y][sizeOver2 + 1]) {
            visited[current.y][sizeOver2 + 1] = true;  // mark this row as visited
        }

        world->SetNodeColor(current, Color::Red.Dark());

        std::vector<Point2D> neighbors = getVisitableNeighbors(world, current);
        if (neighbors.empty()) {
            /*Point2D huntedPoint = hunt(world);
            if (abs(huntedPoint.x) <= sizeOver2 && abs(huntedPoint.y) <= sizeOver2) {
              current = hunt(world);
              world->SetNodeColor(current, Color::Green);
              return true;
            }*/

            state = HUNTING_ROWS;
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
        }
        else {
            int index = Random::Range(0, neighbors.size() - 1);
            Point2D next = neighbors[index];
            removeAdjascentWall(world, next, current);
            current = next;
            world->SetNodeColor(current, Color::Green);

            return true;
        }
    }
    if (state == HUNTING_ROWS) {
        // somewhere in here I should check if ALL columns have been visited within this row; if so, move on to the next row
        if (visited[current.y][sizeOver2 + 1]) {
            state = HUNTING_COLUMNS;
            setRowColor(world, current.y, Color::LightGray);
            world->SetNodeColor(current, Color::Yellow);

            return true;
        }
        else {
            setRowColor(world, current.y, Color::LightGray);
            current = Point2D(current.x, current.y + 1);
            setRowColor(world, current.y, Color::Yellow);

            return true;
        }
    }
    if (state == HUNTING_COLUMNS) {
        if (visited[current.y][current.x]) {
            Point2D neighbor = getRandomNeighbor(world, current);
            if (abs(neighbor.x) <= sizeOver2 && abs(neighbor.y) <= sizeOver2) {
                state = NORMAL;
                removeAdjascentWall(world, neighbor, current);
                if (visited[current.y][current.x]) {
                    world->SetNodeColor(current, Color::Black);
                }
                else {
                    world->SetNodeColor(current, Color::LightGray);
                }
                current = neighbor;
                world->SetNodeColor(current, Color::Green);

                return true;
            }
            else {
                world->SetNodeColor(current, Color::LightGray);
                current = Point2D(current.x + 1, current.y);
                world->SetNodeColor(current, Color::Yellow);

                return true;
            }
        }
        else {
            if (visited[current.y][current.x]) {
                world->SetNodeColor(current, Color::Black);
            }
            else {
                world->SetNodeColor(current, Color::LightGray);
            }
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

void HuntAndKill::setRowColor(World* world, int rowNumber, const Color32& color) {
  int sizeOver2 = world->GetSize() / 2;
  for (int i = -sizeOver2; i <= sizeOver2; i++) {
    if (!visited[rowNumber][i]) {
      world->SetNodeColor(Point2D(i, rowNumber), color);
    }
  }
}