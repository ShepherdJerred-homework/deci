cmake_minimum_required(VERSION 3.7)
project(deci)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES Main.cpp ConsoleHandler.cpp ConsoleHandler.h Editor.cpp Editor.h StartMenu.cpp StartMenu.h FileManager.cpp FileManager.h)
add_executable(deci ${SOURCE_FILES})