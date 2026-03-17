cmake_minimum_required(VERSION 3.14)
project(MUD-Space VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(MUD-Space
    MUD-Space.cpp
    src/Server.cpp
)

target_include_directories(MUD-Space PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(MUD-Space PRIVATE
    Boost::system
)

if(UNIX)
    target_link_libraries(MUD-Space PRIVATE pthread)
endif()
