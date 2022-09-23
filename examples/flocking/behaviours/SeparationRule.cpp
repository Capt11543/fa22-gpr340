#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;

        for (int i = 0; i < neighborhood.size(); i++) {
            Vector2 neighborPosition = neighborhood[i]->transform.position;

            float distanceToNeighbor = Vector2::getDistance(position, neighborPosition);
            if (distanceToNeighbor > 0 && distanceToNeighbor < desiredMinimalDistance) {
                Vector2 oppositeDirection = Vector2::normalized(position - neighborPosition);
                separatingForce += oppositeDirection / (distanceToNeighbor * distanceToNeighbor);
            }
        }
    }

    separatingForce = Vector2::normalized(separatingForce);

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
