// I chose this algorithm because the name sounds badass

#pragma once

#include "../../core/Point2D.h"
#include <map>
#include "../MazeGeneratorBase.h"
#include <vector>
#include "../World.h"

class HuntAndKill : public MazeGeneratorBase {
	public:
		void Clear(World* world) override;
		std::string GetName() override { return "Hunt and Kill"; }
		HuntAndKill(World* world) : current(getRandomPoint(world)) {}
		~HuntAndKill() = default;
		bool Step(World* world) override;
	private:
		Point2D current;
        std::map<int, std::map<int, bool>> visited;

		Point2D getRandomPoint(World* world);
        std::vector<Point2D> getVisitableNeighbors(World* world);
        bool isVisitable(World* world, Point2D point);
};