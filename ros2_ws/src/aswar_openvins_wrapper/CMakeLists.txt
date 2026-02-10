cmake_minimum_required(VERSION 3.16)
project(aswar_openvins_wrapper)

find_package(ament_cmake REQUIRED)

install(DIRECTORY launch config scripts docs
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
