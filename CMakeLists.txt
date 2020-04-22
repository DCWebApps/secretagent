cmake_minimum_required(VERSION 3.5)

project(SecretAgent LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(SecretAgent
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    icons.qrc
    appicon.rc
    version.rc
)

set_target_properties(SecretAgent PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

set_property(TARGET SecretAgent PROPERTY WIN32_EXECUTABLE true)

target_link_libraries(SecretAgent PRIVATE Qt5::Widgets)
