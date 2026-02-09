# cv_cpp17_euroc_demo

C++17 computer vision demo using the EuRoC MAV dataset.

## What it does
Loads a EuRoC stereo sequence and runs an ORB feature stage per frame with FPS overlay.

## Build
Requirements
OpenCV development package
Eigen development package
CMake
Ninja

Build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build

Run
./build/euroc_demo data/euroc/MH_01_easy

## Current Status

This repository integrates OpenVINS into a ROS2 Kilted workspace.

Status:
- ROS2 workspace and OpenVINS submodule integrated
- Wrapper package scaffolded
- ROS2 Kilted compatibility investigation in progress

Known issue:
- OpenVINS ov_msckf requires tf2_geometry_msgs include path adjustments for ROS2 Kilted
- Build currently fails at ov_msckf due to ROS2 header layout differences

Next steps:
- Finalize tf2_geometry_msgs include strategy
- Update ov_msckf CMake dependencies if required
- Complete wrapper launch and run pipeline
