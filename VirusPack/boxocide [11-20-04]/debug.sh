#!/bin/sh

# Delete all old coredump files
rm -f core.*

# Set coredumps to unlimited via ulimit
ulimit -c unlimited

# Start the bot and wait for termination
./agobot3 -debug -debuglevel 10

# Start the bot in gdb with the coredump
gdb ./agobot3 ./core.*
