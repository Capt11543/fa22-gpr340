#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>

class World;

struct QueueEntry {
	Point2D position;
	int weight;

	QueueEntry(Point2D position, int weight) : position(position), weight(weight) {};
	
	bool operator<(const QueueEntry& rhs) const {
		return weight < rhs.weight;
	}
};

class Agent {
	public:
		explicit Agent() = default;;
		virtual Point2D Move(World*) = 0;
};

#endif  // AGENT_H
