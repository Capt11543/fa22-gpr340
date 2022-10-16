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

void pause() {
    // implemented with help from the following StackOverflow posts: 
    // https://stackoverflow.com/a/1452701
    // https://stackoverflow.com/a/3213261
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        system("pause");
    #else
        system("read");
    #endif
}