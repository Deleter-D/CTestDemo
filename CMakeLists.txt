cmake_minimum_required(VERSION 3.10)
project(ctest_demo)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Add options for ROCm and CUDA
option(WITH_ROCM "Build with ROCm support" OFF)
option(WITH_CUDA "Build with CUDA support" OFF)

# Find and link the math library
find_library(MATH_LIBRARY m)

if (WITH_ROCM)
    find_package(HIP REQUIRED)
    find_package(MIOpen REQUIRED)

    set(CMAKE_CXX_COMPILER hipcc)
    set(CMAKE_C_COMPILER hipcc)

    set(MY_DNN_INCLUDE_DIRS ${HIP_INCLUDE_DIRS} ${MIOpen_INCLUDE_DIRS})
    set(MY_DNN_LIBRARIES ${HIP_LIBRARIES} ${MIOpen_LIBRARIES})
    add_definitions(-DWITH_ROCM)
elseif (WITH_CUDA)
    find_package(CUDA REQUIRED)
    set(CUDNN_INCLUDE_DIR /usr/include)  # Adjust this to your cuDNN include path
    set(CUDNN_LIBRARY /usr/lib/libcudnn.so)  # Adjust this to your cuDNN library path
    set(MY_DNN_INCLUDE_DIRS ${CUDA_INCLUDE_DIRS} ${CUDNN_INCLUDE_DIR})
    set(MY_DNN_LIBRARIES ${CUDA_LIBRARIES} ${CUDNN_LIBRARY})
    add_definitions(-DWITH_CUDA)
else()
    message(FATAL_ERROR "Either WITH_ROCM or WITH_CUDA must be ON")
endif()

# Add the executable
add_executable(ctest_demo src/main.cpp src/dnn_test.cpp)

# Link the libraries
target_link_libraries(ctest_demo ${MATH_LIBRARY} ${MY_DNN_LIBRARIES})

# Include directories
include_directories(${MY_DNN_INCLUDE_DIRS})

# Enable testing
enable_testing()

# Add the test
add_test(NAME EnvVarTest COMMAND ctest_demo)

# Set the environment variable for the test
set_tests_properties(EnvVarTest PROPERTIES ENVIRONMENT "LD_LIBRARY_PATH=/work/Paddle/build/python/paddle/libs:\$LD_LIBRARY_PATH")
