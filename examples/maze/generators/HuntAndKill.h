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
		enum class State { // use enum class instead
			DIVING,
			HUNTING_ROWS,
			HUNTING_COLUMNS
		};

		Point2D current;
		State state;
        std::map<int, std::map<int, bool>> visited;
		std::map<int, bool> rowVisited; // make new vector for row visited check (or dynamic array, maybe)

		bool allColumnsVisited(World* world, int rowNumber);
		Point2D getRandomNeighbor(World* world, Point2D point);
		Point2D getRandomPoint(World* world);
        std::vector<Point2D> getVisitableNeighbors(World* w, Point2D p);
        void removeAdjascentWall(World* world, Point2D next, Point2D previous);
        void revertColor(World* world, Point2D point);
        void revertRowColor(World* world, int rowNumber);
        void setRowColor(World* world, int rowNumber, const Color32& color);
};