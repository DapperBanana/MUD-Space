cmake_minimum_required(VERSION 3.16)
project(MUD-Space)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(mud-space
    MUD-Space.cpp
    src/Server.cpp
    src/Session.cpp
    src/CommandParser.cpp
)

target_link_libraries(mud-space ${Boost_LIBRARIES} pthread)
