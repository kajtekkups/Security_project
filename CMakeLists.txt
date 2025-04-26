cmake_minimum_required(VERSION 3.10)
project(Hospitals)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")


# add include folder path
include_directories(${PROJECT_SOURCE_DIR}/include)

# add all source files
file(GLOB SRC_FILES ./src/*.cpp)

add_executable(security_1 main.cpp ${SRC_FILES})

# uncoment this line in case you want run a program in a background
# target_link_options(security_1 PRIVATE "-mwindows")
target_link_libraries(security_1 ws2_32)