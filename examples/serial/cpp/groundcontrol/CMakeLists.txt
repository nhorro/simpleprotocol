cmake_minimum_required(VERSION 3.12)
project(groundcontrol_serial)

# Find Boost
# find_package(Boost REQUIRED system thread)

add_executable(${PROJECT_NAME} 
    groundcontrol.cpp 
    ../serialif/serialif.cpp 
    ../tctm/telecommands.cpp 
    ../tctm/telemetry.cpp 
    main.cpp
)

target_link_libraries(${PROJECT_NAME}  
    Boost::system Boost::thread
)

target_include_directories(${PROJECT_NAME}  
    PRIVATE 
        ../tctm/
        ../serialif/
        ../../../../simpleprotocol-cpp/include/ 
)

# If you need additional flags, you can uncomment and use the following lines:
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
