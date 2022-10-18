#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>
#include <vector>

class World;

struct QueueEntry {
	Point2D position;
	int weight;

	bool operator==(const Point2D& rhs) const;
	QueueEntry(Point2D position, int weight) : position(position), weight(weight) {};
	QueueEntry() = default;
};

class Agent {
	public:
		explicit Agent() = default;
		virtual Point2D Move(World*) = 0;
};

#endif  // AGENT_H
