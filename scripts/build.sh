#!/bin/bash
#SBATCH --partition=edu-medium
#SBATCH --nodelist=edu01
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=02:00:00

#SBATCH --job-name=spmv-build
#SBATCH --output=spmv-build-%j.out
#SBATCH --error=spmv-build-%j.err

module load CUDA/12.1.1

BUILD_DIR="${SLURM_SUBMIT_DIR}/build"
BIN_DIR="${SLURM_SUBMIT_DIR}/bin"

echo "=== Starting Build Process ==="

rm -rf "${BUILD_DIR}" "${BIN_DIR}"
mkdir -p "${BUILD_DIR}"
cmake -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Release
cmake --build "${BUILD_DIR}"

if [ $? -ne 0 ]; then
    echo "Error: Compilation failed. Exiting job."
    exit 1
fi

echo "=== Build Completed Successfully ==="