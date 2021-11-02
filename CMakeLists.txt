cmake_minimum_required(VERSION 3.17)
project(GATSP VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default Build Type : Debug
#if (NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE Debug)
#endif ()

option(GATSP_BUILD_TESTS "Build GATSP's unit tests" ON)

# Project Output Paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(GA_PUBLIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/ga")
set(TSP_PUBLIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/tsp")
set(LIB_PUBLIC_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/libs")


# Third-party libraries
add_subdirectory(deps)

# Project Sources
add_subdirectory(src)

if (GATSP_BUILD_TESTS)
    add_subdirectory(tests)
endif (GATSP_BUILD_TESTS)
