cmake_minimum_required(VERSION 3.2)

project(src)

set(TRACKER tracker.cpp)
set(STORY_TREE storyTree.cpp)
set(GRAPTHVIZ graphVizViewer.cpp)
set(LOC_INFO locInfo.cpp)

add_library(src STATIC tracker.cpp storyTree.cpp graphVizViewer.cpp locInfo.cpp)
