#!/bin/bash

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 record-duration" >&2
  exit 1
fi

# use traps to kill the background logging when script exits
# (it seems like using CTRL-C to send a SIGINT to this script
# also sends a SIGINT to the background logging, so we only need
# a trap for EXIT)
trap 'kill -s SIGINT $!' EXIT

echo "Logging data to temp.log for $1 second(s)"
gz stats > temp.log &

# uncomment the following for debugging shut down behavior
# (can use Facundo's answer from
# https://stackoverflow.com/questions/36369136/how-to-kill-a-background-process-created-in-a-script
# to see if the logging is still running in the background)
#echo "(PID for logging is $!)"

sleep "$1"
