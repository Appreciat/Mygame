cmake_minimum_required(VERSION 3.16)

project(MonopolyEasyX LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT WIN32)
    message(WARNING "This game uses EasyX and Windows APIs. Configure is allowed, but the executable target is only created on Windows.")
    return()
endif()

file(GLOB_RECURSE MONOPOLY_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(monopoly ${MONOPOLY_SOURCES})

target_include_directories(monopoly PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
