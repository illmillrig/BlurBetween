cmake_minimum_required(VERSION 2.8)
project(BlurBetween)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


set(SOURCE_FILES
        src/BlurBetweenCmd.h
        src/BlurBetweenCmd.cpp
        src/Tweener.h
        src/Tweener.cpp
        src/BlurBetweenUI.h
        src/BlurBetweenUI.cpp
        src/pluginMain.cpp
        src/BlurBetween.ui
        )

# Sorry, this is hardcoded
set(CMAKE_MODULE_PATH /run/media/miller/BAGHEERA/cadaver/CMAKE)

# Maya
find_package(Maya REQUIRED)
include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})


# Qt
set(QT_DIR ${MAYA_LOCATION}/bin)
set(QT_CONF_PATH ${QT_DIR}/qt.conf)
set(QT_QMAKE_EXECUTABLE ${QT_DIR}/qmake)
set(QT_MOC_EXECUTABLE ${QT_DIR}/moc)
set(QT_INCLUDE_DIR ${MAYA_INCLUDE_DIR}/qt-4.8.6-include)
set(QT_VERSION_MAJOR 4)
set(QT_VERSION_MINOR 8)
set(QT_VERSION_PATCH 6)

find_package(Qt4 REQUIRED)
include_directories(${QT_INCLUDE_DIR})

#MESSAGE(WARNING ${QT_QMAKE_EXECUTABLE})


# Plugin
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES})
MAYA_PLUGIN(${PROJECT_NAME})
