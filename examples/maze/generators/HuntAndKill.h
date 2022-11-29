// I chose this algorithm because the name sounds badass

#pragma once

#include <Point2D.h>
#include <map>
#include "../MazeGeneratorBase.h"
#include <vector>
#include "../World.h"

class HuntAndKill : public MazeGeneratorBase {
	public:
		void Clear(World* world) override;
		std::string GetName() override { return "Hunt and Kill"; }
        HuntAndKill(World* world);
		~HuntAndKill() = default;
		bool Step(World* world) override;
	private:
		enum State {
			NORMAL,
			HUNTING_ROWS,
			HUNTING_COLUMNS
		};

		Point2D current;
		State state;
        std::map<int, std::map<int, bool>> visited;

		Point2D getRandomNeighbor(World* world, Point2D point);
		Point2D getRandomPoint(World* world);
        std::vector<Point2D> getVisitableNeighbors(World* world, Point2D point);
        Point2D hunt(World* world);
        void removeAdjascentWall(World* world, Point2D next, Point2D previous);
        void setRowColor(World* world, int rowNumber, const Color32& color);
};