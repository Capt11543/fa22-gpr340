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

bool HuntAndKill::Step(World* world) {

}