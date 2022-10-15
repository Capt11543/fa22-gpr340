#pragma once

#include "Agent.h"
#include <iostream>
#include "../../core/Point2D.h"
#include <string>
#include <sstream>
#include <vector>

std::string printQueue(std::vector<QueueEntry> queue) {
    if (queue.empty()) {
        return "The queue is empty!";
    }
    
    std::stringstream output;

    for (int i = 0; i < queue.size(); i++) {
        output << i << ": " << queue[i].toString() << std::endl;
    }

    return output.str();
}