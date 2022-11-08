// I chose this algorithm because the name sounds badass

#pragma once

#include "../../core/Point2D.h"
#include "../MazeGeneratorBase.h"
#include "../World.h"

class HuntAndKill : public MazeGeneratorBase {
	public:
		void Clear(World* world) override;
		std::string GetName() override { return "Hunt and Kill"; }
		HuntAndKill() : start(Point2D(0, 0)), started(false) {}
		~HuntAndKill() = default;
		bool Step(World* world) override;
	private:
		Point2D start;
		bool started;

		Point2D getRandomPoint(World* world);
};