cmake_minimum_required(VERSION 3.21)
project(QGetPrivateByte LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

set_property(GLOBAL PROPERTY AUTOMOC_SOURCE_GROUP "Auto Generated/MOC Files")
set_property(GLOBAL PROPERTY AUTORCC_SOURCE_GROUP "Auto Generated/RCC Files")
set_property(GLOBAL PROPERTY AUTOUIC_SOURCE_GROUP "Auto Generated/UIC Files")

#set(Qt5_ROOT "C:/Qt/Qt5.12.9/5.12.9/msvc2017_64")

find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

file(GLOB SOURCES src/ src/*.cpp)
file(GLOB HEADERS src/ src/*.h)
file(GLOB UIS src/ src/*.ui)

source_group("Sources" FILES ${SOURCES})
source_group("Headers" FILES ${HEADERS})
source_group("Forms" FILES ${UIS})

add_executable(QGetPrivateByte WIN32
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_include_directories(QGetPrivateByte 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(QGetPrivateByte 
    PRIVATE Qt5::Widgets Qt5::PrintSupport
)

if(CMAKE_HOST_WIN32)
    target_compile_options(QGetPrivateByte PRIVATE /wd4819)
endif()

# For customize targets
get_target_property(qmake_exe Qt5::qmake IMPORTED_LOCATION)
get_filename_component(qt_bin_dir ${qmake_exe} DIRECTORY)
set(qt_windeploy_exec "${qt_bin_dir}/windeployqt.exe")
set(qt_lupdate_exec "${qt_bin_dir}/lupdate.exe")
set(qt_lrelease_exec "${qt_bin_dir}/lrelease.exe")

# Target: wideployqt
#add_custom_target(windepolyqt
#    COMMAND "${qt_windeploy_exec}" --verbose 1 --no-translations "${CMAKE_INSTALL_PREFIX}/${INSTALL_FOLDER}/$<TARGET_FILE_NAME:QGetPrivateByte>"
#)
#set_target_properties(windepolyqt
#    PROPERTIES
#        FOLDER ${FOLDER_DEPLOY}
#)