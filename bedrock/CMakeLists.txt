# Hula Bedrock
cmake_minimum_required(VERSION 3.0)
project(Hula LANGUAGES CXX)

# Find dependencies
add_subdirectory(3rdparty/luau)
find_package(SDL2 REQUIRED)

# Set sources
set(SOURCES 
    src/bedrock.cpp)

# Add executable
add_executable(hula ${SOURCES})

# Includes
target_include_directories(hula PRIVATE ${SDL2_INCLUDE_DIRS})

# Copy core directory to build directory
set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../core)
file(COPY ${CORE_DIR} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Add libraries to executable
target_link_libraries(hula PRIVATE ${SDL2_LIBRARIES} Luau.Ast Luau.Compiler Luau.Analysis Luau.VM)

# Set compiler features
target_compile_features(hula PRIVATE cxx_std_17)
