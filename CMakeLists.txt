cmake_minimum_required(VERSION 3.2)

project(TrackerClass)

set(MAIN_FILE main.cpp)

include_directories(include)  # Src headers

add_executable(main ${MAIN_FILE})

add_subdirectory(src)

target_link_libraries(main src)
