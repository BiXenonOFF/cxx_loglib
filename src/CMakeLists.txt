cmake_minimum_required(VERSION 3.8)

set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB TARGET_HEADERS ${TARGET_INCLUDE_DIR}/*.hpp)
file(GLOB TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_library(${PROJECT_NAME} STATIC ${TARGET_HEADERS} ${TARGET_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${TARGET_INCLUDE_DIR})

set(${PROJECT_NAME}_INCLUDE_DIRS ${${PROJECT_NAME}_INCLUDE_DIRS} ${TARGET_INCLUDE_DIR} PARENT_SCOPE)