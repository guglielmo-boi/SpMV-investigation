#!/bin/bash
#SBATCH --partition=edu-medium
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=02:00:00

#SBATCH --job-name=spmv-benchmark
#SBATCH --output=spmv-benchmark-%j.out
#SBATCH --error=spmv-benchmark-%j.err

module load CUDA/12.1.1

./bin/spmv /home/guglielmo.boi/spmv-investigation/data /home/guglielmo.boi/spmv-investigation/log 