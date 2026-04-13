cmake_minimum_required(VERSION 3.26)

project(SpMVProject LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CUDA_STANDARD 17)

# enable CUDA separable compilation
set(CMAKE_CUDA_SEPARABLE_COMPILATION ON)

add_executable(spmv
    src/main.cpp
    src/csr_matrix.cpp
    src/spmv.cu
)

target_include_directories(spmv PRIVATE include)

set_target_properties(spmv PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)