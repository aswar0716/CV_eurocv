cmake_minimum_required(VERSION 3.16)
project(cv_cpp17_euroc_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

add_executable(euroc_demo
    src/main.cpp
    src/euroc_io.cpp
)

target_include_directories(euroc_demo PRIVATE
    ${OpenCV_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    include
)

target_link_libraries(euroc_demo PRIVATE
    ${OpenCV_LIBS}
)
