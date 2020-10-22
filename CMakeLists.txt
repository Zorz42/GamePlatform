cmake_minimum_required(VERSION 3.17)
project(SingleWindowLibrary)

set(CMAKE_CXX_STANDARD 17)

include_directories(SingleWindowLibrary/Headers SingleWindowLibrary/Dependencies SingleWindowLibrary/Headers SingleWindowLibrary/Dependencies/SDL2)
link_directories(SingleWindowLibrary/DependencyLibs)

file(GLOB SOURCES "SingleWindowLibrary/*.cpp")

add_executable(SingleWindowLibrary
        ${SOURCES}
        main.cpp)

target_link_libraries(SingleWindowLibrary SDL2main SDL2 SDL2_image SDL2_ttf)
