#ifndef SPMV_COMMON_HPP
#define SPMV_COMMON_HPP

#include "common.hpp"

#include <cuda_runtime.h>

#define WARP_SIZE 32

__device__
dtype warp_reduce_sum(dtype val);

#endif