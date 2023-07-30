cmake_minimum_required(VERSION 3.15.0)

project(
  simpleprotocol-example
  LANGUAGES CXX
  VERSION ${PACKAGE_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "../include")

target_compile_options(${PROJECT_NAME} PUBLIC ${CXX_TARGET_FLAGS})

# Especificaciones linker
#target_link_libraries(${PROJECT_NAME})