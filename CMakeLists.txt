cmake_minimum_required(VERSION 3.15)
project(SmartHomeSimulator VERSION 1.0 DESCRIPTION "C++ Design Patterns Simulator")

# Enforce C++17 (or C++20 if you prefer) for standard threading and language features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Threading library (required for std::mutex, std::thread)
find_package(Threads REQUIRED)

# Define source files
set(SOURCES
    src/main.cpp
    src/Logger.cpp
    src/DeviceFactory.cpp
    src/Sensor.cpp
    src/HomeFacade.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link threading library
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
