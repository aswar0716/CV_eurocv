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
