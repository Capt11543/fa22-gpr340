#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <map>

class World;

struct QueueEntry {
	Point2D position;
	int weight;

	QueueEntry(Point2D position, int weight) : position(position), weight(weight) {};
	QueueEntry() = default;

	
	//bool operator<(const QueueEntry& rhs) const {
	//	return weight < rhs.weight;
	//}

	/*bool operator==(const QueueEntry& rhs) const {
		return position == rhs.position && weight == rhs.weight;
	}*/

	bool operator==(const Point2D& rhs) const {
		return position.x == rhs.x && position.y == rhs.y;
	}
};

class Agent {
	public:
		explicit Agent() = default;;
		virtual Point2D Move(World*) = 0;
	private:
		bool isExit(Point2D point);
};

#endif  // AGENT_H
