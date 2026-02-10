# Dataset layout contract

This repo does not commit datasets.

Expected local layout:

datasets/
  euroc/
    MH_01_easy/
      mav0/
        cam0/
          data.csv
          data/
        cam1/
          data.csv
          data/
        imu0/
          data.csv

  euroc_ros2bags/
    V1_01_easy/
      <ros2 bag files>

Notes:
- EuRoC raw folder is for offline processing.
- ROS2 bag folder is for OpenVINS tutorial style playback.
