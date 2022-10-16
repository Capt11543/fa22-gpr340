#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) { 
    Point2D cat = world->getCat();
    std::vector<Point2D> path = makePath(world, cat);

    if(!path.empty()) {
      return path[path.size() - 1];
    }
    
    return chooseRandomPoint(world);
}

Point2D Catcher::chooseRandomPoint(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
