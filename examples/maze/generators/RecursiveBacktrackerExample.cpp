#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
<<<<<<< HEAD:examples/maze/generators/RecursiveBacktracker.cpp

bool RecursiveBacktracker::Step(World* w) {
=======
bool RecursiveBacktrackerExample::Step(World* w) {
>>>>>>> upstream/master:examples/maze/generators/RecursiveBacktrackerExample.cpp
  // check if we need to find a new starting point
  if(stack.empty()) {
    auto point = randomStartPoint(w);
    if(point.x==INT_MAX && point.y==INT_MAX)
      return false; // no empty space no fill
    stack.push_back(point);
    w->SetNodeColor(point, Color::Red.Dark());
    // remove a wall when restarting search
    Point2D breakableNeighbor = getBreakableNeighbor(w, point);
    auto delta = breakableNeighbor - point;
    // remove walls
    if (delta.y == -1)  // north
      w->SetNorth(point, false);
    else if (delta.x == 1)  // east
      w->SetEast(point, false);
    else if (delta.y == 1)  // south
      w->SetSouth(point, false);
    else if (delta.x == -1)  // west
      w->SetWest(point, false);
    return true;
  }

  // visit the current element
  auto current = stack.back();
  visited[current.y][current.x] = true;
  w->SetNodeColor(current, Color::Red.Dark());

  // check if we should go deeper
  std::vector<Point2D> visitables = getVisitables(w, current);

  // if we should not go deep, pop one element from the stack
  if(visitables.empty()) {
    for (auto e : stack) {
      w->SetNodeColor(e, Color::Black);
    }
    stack.clear();
    
    return true;
  }
  else { // go deeper
    auto r = Random::Range(0, visitables.size()-1);
    auto next = visitables[r];
    w->SetNodeColor(next, Color::Green);
    stack.push_back(next);
    auto delta = next - current;
    // remove walls
    if(delta.y==-1) // north
      w->SetNorth(current, false);
    else if(delta.x==1) // east
      w->SetEast(current, false);
    else if(delta.y==1) // south
      w->SetSouth(current, false);
    else if(delta.x==-1) // west
      w->SetWest(current, false);
    return true;
  }
}
void RecursiveBacktrackerExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize()/2;

  for(int i=-sideOver2;i<=sideOver2;i++){
    for(int j=-sideOver2;j<=sideOver2;j++){
      visited[i][j] = false;
    }
  }
}
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize()/2;

  for(int y=-sideOver2; y<=sideOver2; y++)
    for(int x=-sideOver2; x<=sideOver2; x++)
      if(!visited[y][x])
        return {x,y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize()/2;
  std::vector<Point2D> visitables;

  // north
  if((abs(p.x)<=sideOver2 && abs(p.y-1)<=sideOver2) && // should be inside the board
      !visited[p.y-1][p.x] && // not visited yet
      w->GetNorth(p)) // has wall
    visitables.emplace_back(p.x, p.y-1);
  // east
  if((abs(p.x+1)<=sideOver2 && abs(p.y)<=sideOver2) && // should be inside the board
      !visited[p.y][p.x+1] && // not visited yet
      w->GetEast(p)) // has wall
    visitables.emplace_back(p.x+1, p.y);
  // south
  if((abs(p.x)<=sideOver2 && abs(p.y+1)<=sideOver2) && // should be inside the board
      !visited[p.y+1][p.x] && // not visited yet
      w->GetSouth(p)) // has wall
    visitables.emplace_back(p.x, p.y+1);
  // west
  if((abs(p.x-1)<=sideOver2 && abs(p.y)<=sideOver2) && // should be inside the board
      !visited[p.y][p.x-1] && // not visited yet
      w->GetWest(p)) // has wall
    visitables.emplace_back(p.x-1, p.y);

  return visitables;
}

Point2D RecursiveBacktracker::getBreakableNeighbor(World* world,
    const Point2D& p) {
  int sideOver2 = world->GetSize() / 2;

  // check each surrounding Point2D, check if the north is inside board and is visited
  // test for north
  if ((abs(p.x) <= sideOver2 &&
       abs(p.y + 1) <= sideOver2) &&  // should be inside the board
      visited[p.y + 1][p.x]) {        // should be visited already
    return Point2D(p.x, p.y + 1);
  } else
  // test for south
  if ((abs(p.x) <= sideOver2 &&
       abs(p.y + 1) <= sideOver2) &&  // should be inside the board
      visited[p.y + 1][p.x]) {        // should be visited already
    return Point2D(p.x, p.y + 1);
  } else
  // test for west
  if ((abs(p.x - 1) <= sideOver2 &&
       abs(p.y) <= sideOver2) &&  // should be inside the board
      visited[p.y][p.x - 1]) {        // should be visited already
    return Point2D(p.x - 1, p.y);
  } else
  // test for east
  if ((abs(p.x + 1) <= sideOver2 &&
       abs(p.y) <= sideOver2) &&  // should be inside the board
      visited[p.y][p.x + 1]) {    // should be visited already
    return Point2D(p.x + 1, p.y);
  } else {
    return Point2D(INT_MAX, INT_MAX);
  }
}