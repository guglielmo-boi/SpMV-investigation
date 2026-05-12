#!/usr/bin/env python3

import argparse
import csv
import math
from pathlib import Path
from collections import defaultdict


CSV_FILES = [
    "csr_adaptive.csv",
    "csr_stream.csv",
    "csr_vector.csv",
    "cusparse.csv",
]


def read_kernel_gflops(csv_path):
    """
    Reads kernel_gflops values grouped by matrix_id from a CSV file.
    """
    values = defaultdict(list)

    with open(csv_path, "r", newline="") as f:
        reader = csv.DictReader(f)

        for row in reader:
            matrix_id = row["matrix_id"]
            kernel_gflops = float(row["kernel_gflops"])

            values[matrix_id].append(kernel_gflops)

    return values


def compute_statistics(samples):
    """
    Computes:
    - mean
    - min
    - max
    - MSE (against the mean)
    - standard deviation
    """
    n = len(samples)

    if n == 0:
        return None

    mean = sum(samples) / n
    minimum = min(samples)
    maximum = max(samples)

    mse = sum((x - mean) ** 2 for x in samples) / n
    stddev = math.sqrt(mse)

    return {
        "mean": mean,
        "min": minimum,
        "max": maximum,
        "mse": mse,
        "stddev": stddev,
    }


def process_method(data_dir, output_dir, filename):
    """
    Processes all CSV files with the same method name
    across all subfolders.
    """
    aggregated = defaultdict(list)

    # Search all subdirectories
    for subdir in data_dir.iterdir():
        if not subdir.is_dir():
            continue

        csv_path = subdir / filename

        if not csv_path.exists():
            print(f"Warning: missing file {csv_path}")
            continue

        method_values = read_kernel_gflops(csv_path)

        for matrix_id, values in method_values.items():
            aggregated[matrix_id].extend(values)

    # Output CSV
    output_path = output_dir / filename

    with open(output_path, "w", newline="") as f:
        writer = csv.writer(f)

        writer.writerow([
            "matrix_id",
            "mean_kernel_gflops",
            "min_kernel_gflops",
            "max_kernel_gflops",
            "mse_kernel_gflops",
            "stddev_kernel_gflops",
        ])

        for matrix_id in sorted(aggregated.keys()):
            stats = compute_statistics(aggregated[matrix_id])

            writer.writerow([
                matrix_id,
                f"{stats['mean']:.3f}",
                f"{stats['min']:.3f}",
                f"{stats['max']:.3f}",
                f"{stats['mse']:.3f}",
                f"{stats['stddev']:.3f}",
            ])

    print(f"Generated: {output_path}")


def main():
    parser = argparse.ArgumentParser(
        description="Aggregate SpMV benchmark CSV files."
    )

    parser.add_argument(
        "data_dir",
        help="Path to input data directory"
    )

    parser.add_argument(
        "output_dir",
        help="Path to output directory"
    )

    args = parser.parse_args()

    data_dir = Path(args.data_dir)
    output_dir = Path(args.output_dir)

    output_dir.mkdir(parents=True, exist_ok=True)

    for filename in CSV_FILES:
        process_method(data_dir, output_dir, filename)


if __name__ == "__main__":
    main()