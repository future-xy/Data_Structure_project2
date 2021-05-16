cmake_minimum_required(VERSION 3.20.1)

project(data_structure_project2)

set(SOURCES
    src/main.cpp
    src/Airport.cpp
    src/Plane.cpp
    src/Runway.cpp
)

add_executable(data_structure_project2 ${SOURCES})

target_include_directories(data_structure_project2
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
