#!/bin/bash
#SBATCH --partition=edu-medium
#SBATCH --nodelist=edu01
#SBATCH --account=gpu.computing26
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=1
#SBATCH --time=02:00:00

#SBATCH --job-name=spmv-ncu
#SBATCH --output=spmv-ncu-%j.out
#SBATCH --error=spmv-ncu-%j.err

module load CUDA/12.1.1

export TMPDIR=$HOME/tmp/$SLURM_JOB_ID
mkdir -p $TMPDIR

ncu \
    --set speedOfLight \
    --target-processes all \
    --export ncu-report-${SLURM_ARRAY_TASK_ID} \
    ./bin/spmv \
    /home/guglielmo.boi/spmv-investigation/data \
    /home/guglielmo.boi/spmv-investigation/log