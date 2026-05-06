#!/bin/bash
#SBATCH --partition=edu-short
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:05:00

#SBATCH --job-name=spmv-main
#SBATCH --output=spmv-main-%j.out
#SBATCH --error=spmv-main-%j.err

module load CUDA/12.1.1

./bin/spmv /home/guglielmo.boi/spmv-investigation/data /home/guglielmo.boi/spmv-investigation/log 