#!/bin/bash
# This file can be used as a top-level build system. It works by moving the module files into the necessary positions.
# Then, it calls the build system used by PX4 to include new modules.

mkdir ./external/PX4-Autopilot/src/modules/sprayer

cp CMakeLists.txt ./external/PX4-Autopilot/src/modules/sprayer/CmakeLists.txt
cp Kconfig ./external/PX4-Autopilot/src/modules/sprayer/Kconfig
cp sprayer.c ./external/PX4-Autopilot/src/modules/sprayer/sprayer.c

cd ./external/PX4-Autopilot

make cubepilot_cubeorangeplus
