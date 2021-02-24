# GazeboSim_performance_inspector

Tools for analyzing/comparing performance between Gazebo classic (http://gazebosim.org/) and Ignition (https://ignitionrobotics.org/home)

## Requirements

1. [Ignition Dome](https://ignitionrobotics.org/docs/dome) or [Gazebo 11](http://gazebosim.org/tutorials?cat=install)
1. [NumPy](https://numpy.org/)
1. [Matplotlib](https://matplotlib.org/stable/users/installing.html)
1. [CMake](https://cmake.org/download/)
1. [Boost - Program Options](https://www.boost.org/doc/libs/1_75_0/doc/html/program_options.html)
1. C++11 (or newer)

The setup and usage steps assume that you have cloned the repository to `~/` (`$HOME`).

## Setup

### Gazebo 11

There is no additional setup required for Gazebo 11.
Make sure you have all of the [requirements](#requirements) installed, and then look at the [usage](#usage) section.

### Ignition Dome

```
cd ~/GazeboSim_performance_inspector/
mkdir build
cd build/
cmake ..
make
```

## Usage

### Gazebo 11

1. Start a simulation:
```
gazebo worlds/shapes.world
```

2. Run the `log_gazebo_11_metrics.bash` script, passing the amount of time (in seconds) you'd like to record metrics for:
```
cd ~/GazeboSim_performance_inspector/scripts/

# the following command will log metrics for 3 seconds
./log_gazebo_11_metrics.bash 3
```

3. Data should have been logged to `temp.log`, but is not in the format that is needed for plotting metrics.
   Run the following command to create a new file called `gazebo_11.log` which contains the RTF data from `temp.log` in a plottable format:
```
awk -F\[ '{ split($2, splits, "]"); print splits[1] }' < temp.log > gazebo_11.log
```

### Ignition Dome

Running the steps in the [setup](#setup) section above should have created an executable named `performance_metrics`.
This executable will subscribe to an ignition topic that contains performance metrics, and log performance metrics to a file for a certain amount of time.

You can learn more about how to use `performance metrics` by using the `--help` flag:
```
$ ./performance_metrics --help
```

Here's an example of how to log performance metrics from the [shapes.sdf](https://github.com/ignitionrobotics/ign-gazebo/blob/89987404180f38dafe5542d677ba97c8f4ce23d9/examples/worlds/shapes.sdf) world:

1. Start a simulation:
```
# this will use the default physics engine (DART)
ign gazebo -r shapes.sdf

# to run with TPE (trivial physics engine), run this command instead
ign gazebo -r shapes.sdf --physics-engine ignition-physics-tpe-plugin
```

2. Run `performance_metrics`:
```
cd ~/GazeboSim_performance_inspector/build/

# the following command will log metrics for 3 seconds
./performance_metrics --time 3
```

### Comparing Gazebo 11 and Ignition Dome

Once you have recorded performance metrics for Gazebo 11 and Ignition Dome, you can use `plot_metrics.py` to plot the metrics for comparison:
```
$ python3 ~/GazeboSim_performance_inspector/scripts/plot_metrics.py -h
```

### Getting Additional Performance Statistics

If you'd like to learn more about how a particular simulator's metrics, you can use `metric_stats.py` to get some basic statistics about metrics that have been logged:
```
$ python3 ~/GazeboSim_performance_inspector/scripts/metric_stats.py -h
```

## Help

For help with things like converting SDF files to work between Gazebo 11 and Ignition Dome, take a look at [this post](https://community.gazebosim.org/t/migration-from-gazebo-classic-to-ignition-gazebo/805) about Gazebo classic -> Ignition migration.
