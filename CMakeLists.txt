cmake_minimum_required(VERSION 2.8.11)
project(2048)

set(CMAKE_CXX_FLAGS "-m64 -pipe -pedantic -Wall -Wextra -O2 -Wall -W -D_REENTRANT ")

#c++11 support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

ADD_DEFINITIONS(${QT_DEFINITIONS})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(HW_GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gui)
subdirs(gui)

set(HW_CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
subdirs(core)

include_directories(QT_INCLUDE_DIR ${HW_GUI_DIR} ${HW_CORE_DIR})

FIND_PACKAGE(Qt5Core)
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE(Qt5Network)
FIND_PACKAGE(Qt5Gui)

file(GLOB SRC
    "*.h"
    "*.cpp"
    "gui/*.h"
    "gui/*.cpp"
    "core/*.h"
    "core/*.cpp"
    
)

QT5_WRAP_UI(UIS
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/mainwindow.ui
)

QT5_WRAP_CPP(CPPS

    ${CMAKE_CURRENT_SOURCE_DIR}/gui/qgameboard.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/qgameoverwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/qresetbutton.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/qtile.h
    ${CMAKE_CURRENT_SOURCE_DIR}/gui/mainwindow.h
)

ADD_EXECUTABLE(${PROJECT_NAME} main.cpp ${SRC} ${UIS})

# Old Interfaces:
 set_property(TARGET ${PROJECT_NAME}
    APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG DEBUG_MODE )

 set_property(DIRECTORY
    APPEND PROPERTY COMPILE_DEFINITIONS_DEBUG DIR_DEBUG_MODE )

qt5_use_modules(${PROJECT_NAME} Widgets Core Gui Network)
