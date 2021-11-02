enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

function(gatsp_test test_file test_lib)
    get_filename_component(test_target_name "${test_file}" NAME_WE)

    message(STATUS "Test case: " ${test_target_name})
    message(STATUS "Test case source file: " ${test_file})

    add_executable("${test_target_name}")
    target_sources("${test_target_name}" PRIVATE "${test_file}")
    target_link_libraries("${test_target_name}" PRIVATE ${test_lib} gtest_main)
    add_test(
            NAME "${test_target_name}"
            COMMAND "${test_target_name}"
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
endfunction(gatsp_test)

gatsp_test("${CMAKE_CURRENT_SOURCE_DIR}/tsp/TSPLIBTest.cpp" "tsp")
gatsp_test("${CMAKE_CURRENT_SOURCE_DIR}/tsp/TSPTest.cpp" "tsp")
