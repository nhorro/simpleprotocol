cmake_minimum_required(VERSION 3.12)
project(SerialCommunication)

set(CMAKE_CXX_STANDARD 14)

# Find Boost
find_package(Boost REQUIRED system thread)

add_subdirectory(groundcontrol)

# If you need additional flags, you can uncomment and use the following lines:
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
