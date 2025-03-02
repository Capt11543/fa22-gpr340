#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;

    // todo: add your code here to make a force towards the center of mass
    // hint: iterate over the neighborhood
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;

        for (int i = 0; i < neighborhood.size(); i++) {
            cohesionForce += neighborhood[i]->transform.position - boid->transform.position;
        }

        cohesionForce /= neighborhood.size();
    }

    cohesionForce = Vector2::normalized(cohesionForce);

    return cohesionForce;
}