# Minimum CMake version required
cmake_minimum_required(VERSION 3.29)

# Project name and version
project(COP2003_final VERSION 1.0)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate the Qt installation (adjust the path to your actual Qt installation)
set(CMAKE_PREFIX_PATH "/Users/robertbenstine/Qt/6.8.0/macos/lib/cmake")

# Find the required Qt6 packages (add more components if needed)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Add the main executable for the project
add_executable(COP2003_final main.cpp
        DC_Protag..h)

# Link the Qt libraries to the target (adjust as needed for your project)
target_link_libraries(COP2003_final Qt6::Widgets)


