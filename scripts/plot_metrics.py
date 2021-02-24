import argparse
import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
            description='Plot simulation performance metrics.')
    parser.add_argument('gazebo_file', type=str,
            help='The file containing the Gazebo 11 data to be plotted')
    parser.add_argument('ign_file', type=str,
            help='The file containing the Ignition data to be plotted')
    parser.add_argument('--img', type=str,
            help="The name of the file the plot should be saved to. If this argument is not set, the plot won't be saved to a file.")
    args = parser.parse_args()

    gazebo_data = np.loadtxt(args.gazebo_file, dtype=np.float32)
    ign_data = np.loadtxt(args.ign_file, dtype=np.float32)

    fig = plt.figure()
    ax = fig.add_subplot(111) # the big subplot
    ax1 = fig.add_subplot(121)
    ax2 = fig.add_subplot(122)

    # Turn off axis lines and ticks of the big subplot
    ax.spines['top'].set_color('none')
    ax.spines['bottom'].set_color('none')
    ax.spines['left'].set_color('none')
    ax.spines['right'].set_color('none')
    ax.tick_params(labelcolor='w', top=False, bottom=False, left=False, right=False)

    # Set common axis labels
    ax.set_ylabel("RTF")
    ax.set_xlabel("Samples Over Time")

    # Plot the data
    y_axis_range = [0,1.1]
    ax1.plot(gazebo_data)
    ax1.set_ylim(y_axis_range)
    ax1.set_title("Gazebo 11")
    ax2.plot(ign_data)
    ax2.set_ylim(y_axis_range)
    ax2.set_yticks([])
    ax2.set_title("Ignition Dome")

    if args.img is not None:
        plt.savefig(args.img)

    plt.show()
