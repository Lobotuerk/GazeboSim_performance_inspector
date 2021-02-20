import argparse
import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            description='Plot simulation performance metrics.')
    parser.add_argument('file', type=str,
            help='The file containing the data to be plotted')
    args = parser.parse_args()

    data = np.loadtxt(args.file, dtype=np.float32)

    plt.plot(data)
    plt.ylabel("RTF")
    plt.xlabel("Samples Over Time")
    plt.title(os.path.basename(args.file))
    plt.show()

    '''
    # this can be used get some statistics about the RTF
    plt.subplot(121)
    plt.plot(data)
    plt.subplot(122)
    plt.boxplot(data, showfliers=False)
    plt.show()
    '''
