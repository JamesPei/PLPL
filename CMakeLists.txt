cmake_minimum_required(VERSION 3.5)

project (PLPL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(lexer)
add_subdirectory(inter)
add_subdirectory(parser)

add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/main.cpp")
target_link_libraries("${PROJECT_NAME}" Lexer)
target_link_libraries("${PROJECT_NAME}" Inter)
target_link_libraries("${PROJECT_NAME}" Parser)