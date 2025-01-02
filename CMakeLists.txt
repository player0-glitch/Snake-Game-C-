cmake_minimum_required(VERSION 3.30.5)
project(snake)

#Setting C++ Standard
set(CMAKE_CXX_STANDARD 17)

#Setting compile flags (debugging symboles)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra -O0")
#creating compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

#source directory
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

#defining the executable 
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -g -O0)
#setting up SFML stuff
# set(SFML_DIR "C:/usr/lib64/cmake/SFML")
set(SFML_LIBS sfml-graphics sfml-audio sfml-window sfml-system)
# set(SFML_STATIC_LIBRARIES TRUE)
# find_package(SFML COMPONENTS sfml-graphics sfml-audio sfml-window sfml-system REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBS} ${SFML_DEPENDENCIES})
