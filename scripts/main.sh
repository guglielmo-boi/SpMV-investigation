#!/bin/bash
#SBATCH --partition=edu-short
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00

#SBATCH --job-name=spmv-test
#SBATCH --output=spmv-%j.out
#SBATCH --error=spmv-%j.err

module load CUDA/12.1.1

./bin/spmv