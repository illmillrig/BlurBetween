cmake_minimum_required(VERSION 3.5)
project(BlurBetween)


set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCE_FILES
    BlurBetween/BlurBetweenCmd.cpp
    BlurBetween/BlurBetweenCmd.h
    BlurBetween/pluginMain.cpp
    BlurBetween/Tweener.cpp
    BlurBetween/Tweener.h
    blurBetween.ui
    blurBetweenUI.py)

# Sorry, this is hardcoded
set(CMAKE_MODULE_PATH /media/miller/BAGHEERA/cadaver/CMAKE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})