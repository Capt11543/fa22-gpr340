file(GLOB CONCURRENCY_SRC
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

file(GLOB CONCURRENCY_INC
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
        )

SET(CONCURRENCY_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
add_library(concurrency ${CONCURRENCY_SRC} ${CONCURRENCY_INC})
