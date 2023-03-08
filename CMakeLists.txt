cmake_minimum_required(VERSION 3.21)
project(QGetPrivateByte LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src *.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_LIST_DIR}/src *.h)
file(GLOB UIS ${CMAKE_CURRENT_LIST_DIR}/src *.ui)

set(VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)

add_executable(QGetPrivateByte WIN32
    ${SOURCES}
    ${HEADERS}
    ${UIS}

    ${VENDOR_DIR}/qcustomplot/qcustomplot.cpp
    ${VENDOR_DIR}/qcustomplot/qcustomplot.h
)