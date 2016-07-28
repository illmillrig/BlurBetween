cmake_minimum_required(VERSION 2.8)
project(BlurBetween)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(SOURCE_FILES
        BlurBetween/BlurBetweenCmd.h
        BlurBetween/BlurBetweenCmd.cpp
        BlurBetween/Tweener.h
        BlurBetween/Tweener.cpp
        BlurBetween/BlurTweenUI.h
        BlurBetween/BlurTweenUI.cpp
        BlurBetween/pluginMain.cpp
        blurBetween.ui
        BlurBetween/blurBetween_ui.h
        )

# Sorry, this is hardcoded
set(CMAKE_MODULE_PATH /media/miller/BAGHEERA/cadaver/CMAKE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Maya REQUIRED)

include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})


include_directories(/usr/local/Trolltech/Qt-4.8.6/include)
link_directories(/usr/local/Trolltech/Qt-4.8.6/bin)
find_package(Qt4 COMPONENTS /usr/local/Trolltech/Qt-4.8.6/bin/moc)


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})

MAYA_PLUGIN(${PROJECT_NAME})