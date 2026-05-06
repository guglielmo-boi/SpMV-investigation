#!/bin/bash
#SBATCH --partition=edu-short
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00

#SBATCH --job-name=spmv-ctest
#SBATCH --output=spmv-ctest-%j.out
#SBATCH --error=spmv-ctest-%j.err

module load CUDA/12.1.1

set -e

cd $SLURM_SUBMIT_DIR/build

ctest --output-on-failure