import argparse
import numpy as np

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            description='Get statistics about performance metrics.')
    parser.add_argument('file', type=str,
            help='The file containing the metrics to analyze.')
    args = parser.parse_args()

    data = np.loadtxt(args.file, dtype=np.float32)
    print("mean:\t", np.mean(data))
    print("median:\t", np.median(data))
    print("min:\t", data.min())
    print("max:\t", data.max())
