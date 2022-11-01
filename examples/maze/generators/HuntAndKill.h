// I chose this algorithm because the name sounds badass

#pragma once

#include "../MazeGeneratorBase.h"

class HuntAndKill : public MazeGeneratorBase {
	public:
		std::string GetName() override { return "Hunt and Kill"; }
		bool Step(World* world) override;
		void Clear(World* world) override;
		HuntAndKill() = default;
		~HuntAndKill() = default;
};