# SpMV CSR-Based Methods Investigation on GPU

This project investigates different GPU implementations of Sparse Matrix-Vector Multiplication (SpMV) using the compressed sparse row (CSR) sparse matrix format.

* CSR-Vector
* CSR-Stream
* CSR-Adaptive
* cuSPARSE (baseline)

The project evaluates kernel execution time, GFLOPS, memory traffic, Streaming Multiprocessor throughput, and bandwidth utilization across several sparse matrices from the SuiteSparse collection.

## Build

```bash
cmake -B build
cmake --build build
```

## Run Benchmarks

```bash
sbatch ./scripts/benchmark.sh
```

## Run Tests

```bash
sbatch ./scripts/test.sh
```

## Repository Structure

```text
include/      Header files
src/          Source code
tests/        SpMV implementations tests
scripts/      SLURM and Python scripts
data/         Sparse matrix datasets (mtx format)
results/      Benchmark outputs
log/          Execution logs
references/   Papers and reference material
external/     External dependencies
```
