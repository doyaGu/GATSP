add_library(ga STATIC)

set(GA_PRIVATE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(ga
        PRIVATE
        "${GA_PRIVATE_SOURCE_DIR}/GeneticAlgorithm.cpp"
        "${GA_PRIVATE_SOURCE_DIR}/Environment.cpp"
        "${GA_PRIVATE_SOURCE_DIR}/Chromosome.cpp"
        "${LIB_PUBLIC_INCLUDE_DIR}/random.hpp"
        # Only CMake 3.3+ supports PUBLIC sources in targets exported by "install".
        $<$<VERSION_GREATER:CMAKE_VERSION,3.2>:PUBLIC>
        "${GA_PUBLIC_INCLUDE_DIR}/GeneticAlgorithm.h"
        "${GA_PUBLIC_INCLUDE_DIR}/Environment.h"
        "${GA_PUBLIC_INCLUDE_DIR}/Chromosome.h")

target_include_directories(ga
        PRIVATE
        "$<BUILD_INTERFACE:${LIB_PUBLIC_INCLUDE_DIR}>"
        PUBLIC
        "$<BUILD_INTERFACE:${GA_PUBLIC_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/ga>")

# Enable a reasonable set of warnings (no, -Wextra is not reasonable)
target_compile_options(ga
        PRIVATE
        "$<$<C_COMPILER_ID:AppleClang>:-Wall>"
        "$<$<C_COMPILER_ID:Clang>:-Wall>"
        "$<$<C_COMPILER_ID:GNU>:-Wall>")