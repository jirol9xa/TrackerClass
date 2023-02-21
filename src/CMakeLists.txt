cmake_minimum_required(VERSION 3.2)

project(src)

set(TRACKER Tracker.cpp)
set(STORY_TREE StoryTree.cpp)
set(GRAPTHVIZ GraphVizViewer.cpp)
set(LOC_INFO LocInfo.cpp)

add_library(src STATIC Tracker.cpp StoryTree.cpp GraphVizViewer.cpp LocInfo.cpp)
