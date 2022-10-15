#include <algorithm>
#include "Cat.h"
#include "functions.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include "World.h"

Point2D Cat::Move(World* world) {
    Point2D cat = world->getCat();
    
    std::map<int, std::map<int, bool>> visited;
    std::map<int, std::map<int, Point2D>> cameFrom;
    
    Point2D endPoint = Point2D();
    std::vector<QueueEntry> queue;
    queue.push_back({ cat, 0 });
    std::cout << printQueue(queue) << std::endl;

    while (!queue.empty()) {
        QueueEntry head = queue[0];
        std::cout << "Head: " << head.toString() << std::endl;
        
        queue.erase(queue.begin());
        std::cout << printQueue(queue) << std::endl;

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
            if (abs(neighbor.x) >= world->getWorldSideSize() / 2 || abs(neighbor.y) >= world->getWorldSideSize() / 2) {
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
            queue.push_back({ neighbor, head.weight + 1 });
            std::cout << printQueue(queue) << std::endl;

            // mark the neighbor as having come from the head
            cameFrom[neighbor.x][neighbor.y] = head.position;
        }

        // write win condition (path found condition) and navigation process here
        // if the absolute value of the x or the y is equal to world.sideSize / 2;
    }

    // Build path
    std::vector<Point2D> path;
    Point2D head = endPoint;
    while (head != cat) {
      path.insert(path.begin(), head);
      head = cameFrom[head.x][head.y];
    }

    // Return the first point in the path if the path is not empty
    if (!path.empty()) {
      return path[0];
    }

    // Return a random point if the path is empty
    int rand = Random::Range(0, 5);
    Point2D pos = world->getCat();
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
