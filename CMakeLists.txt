cmake_minimum_required(VERSION 3.0)
project(USG)

#--------------------------------------------------------------------
# Set GLFW variables
#--------------------------------------------------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------
include_directories(include)

add_subdirectory(src)
