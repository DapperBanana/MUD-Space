cmake_minimum_required(VERSION 3.10)
project(MUDSpace)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system asio)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DBOOST_ALL_NO_LIB)
endif()


set(SOURCE_FILES
        MUD-Space.cpp
        src/Server.cpp
        src/Session.cpp
        src/CommandParser.cpp
        src/CommandDispatcher.cpp
        src/Game.cpp
        include/Server.h
        include/Session.h
        include/CommandParser.h
        include/CommandDispatcher.h
        include/Game.h
        )

add_executable(MUDSpace ${SOURCE_FILES})

target_link_libraries(MUDSpace ${Boost_LIBRARIES})
