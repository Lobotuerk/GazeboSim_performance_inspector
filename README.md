# GazeboSim_performance_inspector

Tools for analyzing/comparing performance between Gazebo classic (http://gazebosim.org/) and Ignition (https://ignitionrobotics.org/home)

## Requirements

1. [Ignition Dome](https://ignitionrobotics.org/docs/dome) or [Gazebo 11](http://gazebosim.org/tutorials?cat=install)
1. [NumPy](https://numpy.org/)
1. [Matplotlib](https://matplotlib.org/stable/users/installing.html)
1. [CMake](https://cmake.org/download/)
1. [Boost - Program Options](https://www.boost.org/doc/libs/1_75_0/doc/html/program_options.html)
1. C++11 (or newer)

## Setup

The following steps assume that you have cloned the repository to `~/` (`$HOME`).

```
cd ~/GazeboSim_performance_inspector/

# create a build directory
mkdir build
cd build/

# next, configure the build. Pick the step below that matches your platform
# (i.e., use IGN_DOME if you have Ignition Dome installed,
# and use GAZEBO_11 if you have Gazebo 11 installed)

# configure the build for Ignition Dome
cmake .. -DIGN_DOME=ON

# configure the build for Gazebo 11
cmake .. -DGAZEBO_11=ON

# run the build
make
```

## Usage

Running the steps above should have created an executable named `performance_metrics`.
This executable will subscribe to a simulation topic that contains performance metrics, and log performance metrics to a file for a certain amount of time.

You can learn more about how to use `performance metrics` by using the `--help` flag:
```
$ ./performance_metrics --help
Allowed options:
  -h [ --help ]         Produce help message
  --topic arg (=/stats)  The topic to subscribe to that contains performance
                        metrics
  --time arg (=10)      How long to record metrics for, in seconds
  --file arg (=metrics.log) The file to log metrics to
```

The default topic should work with Ignition topics.
For Gazebo topics, you'll probably need to change the topic to `~/world_stats`.

### Example Usage

1. Start a simulator:
```
# If you're using Ignition:
ign gazebo -r shapes.sdf

# If you're using Gazebo 11:
gazebo worlds/shapes.world
```

2. Run `performance_metrics`:
```
cd ~/GazeboSim_performance_inspector/build/

# If you're using Ignition:
./performance_metrics

# If you're using Gazebo 11:
./performance_metrics --topic "~/world_stats"
```

3. Visualize performance once logging is done:
```
cd ~/GazeboSim_performance_inspector
python3 scripts/rtf_plotter.py build/rtf.log
```

## Help

For help with things like converting SDF files to work between Gazebo 11 and Ignition Dome, take a look at [this post](https://community.gazebosim.org/t/migration-from-gazebo-classic-to-ignition-gazebo/805) about Gazebo classic -> Ignition migration.
