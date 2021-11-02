# Project Libraries
add_subdirectory(ga)
add_subdirectory(tsp)

add_executable(gatsp main.cpp)
target_link_libraries(gatsp PRIVATE ga tsp)
target_include_directories(gatsp
        PRIVATE
        "$<BUILD_INTERFACE:${LIB_PUBLIC_INCLUDE_DIR}>")

# Enable a reasonable set of warnings (no, -Wextra is not reasonable)
target_compile_options(gatsp
        PRIVATE
        "$<$<C_COMPILER_ID:AppleClang>:-Wall>"
        "$<$<C_COMPILER_ID:Clang>:-Wall>"
        "$<$<C_COMPILER_ID:GNU>:-Wall>")