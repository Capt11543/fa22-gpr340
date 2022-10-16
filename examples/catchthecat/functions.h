#pragma once

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