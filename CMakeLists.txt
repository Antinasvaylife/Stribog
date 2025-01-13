cmake_minimum_required(VERSION 3.16.0)

set(PROJECT_NAME Stribog)

project(${PROJECT_NAME} LANGUAGES C)

file(GLOB C_SOURCES *.c)

file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${C_SOURCES} ${HEADERS})
