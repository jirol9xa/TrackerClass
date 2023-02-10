cmake_minimum_required(VERSION 3.2)

project(src)

set(TRACKER tracker.cpp)

add_library(src STATIC ${TRACKER})
