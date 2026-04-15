cmake_minimum_required(VERSION 3.26)

project(spmv)

set(CMAKE_CXX_STANDARD 17)

# -------------------------
# Executable
# -------------------------
add_executable(spmv
    src/main.cpp
    src/csr_matrix.cpp
    src/dense_vector.cpp
    src/mtx_parser.cpp
    src/spmv.cpp
)

target_include_directories(spmv PRIVATE include)

set_target_properties(spmv PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# -------------------------
# GoogleTest
# -------------------------
add_subdirectory(external/googletest-1.17.0)

enable_testing()

add_executable(spmv_tests
    tests/test_spmv.cpp
    src/csr_matrix.cpp
    src/dense_vector.cpp
    src/mtx_parser.cpp
    src/spmv.cpp
)

target_include_directories(spmv_tests PRIVATE include)

target_link_libraries(spmv_tests PRIVATE gtest_main)

add_test(NAME SpMVTests COMMAND spmv_tests)