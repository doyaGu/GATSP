add_library(tsp STATIC)

set(TSP_PRIVATE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(tsp
        PRIVATE
        "${TSP_PRIVATE_SOURCE_DIR}/TSP.cpp"
        "${TSP_PRIVATE_SOURCE_DIR}/TSPLIB.cpp"
        "${TSP_PRIVATE_SOURCE_DIR}/DistanceFunctions.cpp"
        "${TSP_PRIVATE_SOURCE_DIR}/DistanceFunctions.h"
        # Only CMake 3.3+ supports PUBLIC sources in targets exported by "install".
        $<$<VERSION_GREATER:CMAKE_VERSION,3.2>:PUBLIC>
        "${TSP_PUBLIC_INCLUDE_DIR}/TSP.h"
        "${TSP_PUBLIC_INCLUDE_DIR}/TSPLIB.h"
        "${TSP_PUBLIC_INCLUDE_DIR}/Type.h"
        "${TSP_PUBLIC_INCLUDE_DIR}/Enums.h")

target_include_directories(tsp
        PRIVATE
        "$<BUILD_INTERFACE:${LIB_PUBLIC_INCLUDE_DIR}>"
        PUBLIC
        "$<BUILD_INTERFACE:${TSP_PUBLIC_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/tsp>")

#target_compile_options(tsp
#        PRIVATE
#        $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-depth=8196>
#        $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-loop-limit=8196>
#        $<$<CXX_COMPILER_ID:GNU>:-fconstexpr-ops-limit=8196>)

# Enable a reasonable set of warnings (no, -Wextra is not reasonable)
target_compile_options(tsp
        PRIVATE
        "$<$<C_COMPILER_ID:AppleClang>:-Wall>"
        "$<$<C_COMPILER_ID:Clang>:-Wall>"
        "$<$<C_COMPILER_ID:GNU>:-Wall>")