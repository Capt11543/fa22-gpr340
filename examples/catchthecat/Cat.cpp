#include <algorithm>
#include "Cat.h"
#include "functions.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "World.h"

Point2D Cat::Move(World* world) {
    Point2D cat = world->getCat();
    std::vector<Point2D> path = makePath(world, cat);

    // Return the first point in the path if the path is not empty
    if (!path.empty()) {
      return path[0];
    }

    // Return a random point if the path is empty
    return chooseRandomPoint(cat);
}

Point2D Cat::chooseRandomPoint(Point2D pos) {
  int rand = Random::Range(0, 5);
  switch (rand) {
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
