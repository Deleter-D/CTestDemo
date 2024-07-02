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
    set(CMAKE_CXX_COMPILER hipcc)
    set(CMAKE_C_COMPILER hipcc)

    find_package(HIP REQUIRED)
    find_library(MIOPEN_LIBRARY libMIOpen.so HINTS /opt/dtk-23.10.1/miopen/lib REQUIRED)
    find_path(MIOPEN_INCLUDE_DIR "miopen/miopen.h" PATHS /opt/dtk-23.10.1/miopen/include)
    set(MY_DNN_INCLUDE_DIRS ${HIP_INCLUDE_DIRS} ${MIOPEN_INCLUDE_DIR})
    set(MY_DNN_LIBRARIES ${HIP_LIBRARIES} ${MIOPEN_LIBRARY})
    add_definitions(-DWITH_ROCM)
elseif (WITH_CUDA)
    find_package(CUDA REQUIRED)
    find_library(CUDNN_LIBRARY libcudnn.so HINTS /usr/lib REQUIRED)
    find_path(CUDNN_INCLUDE_DIR cudnn.h PATHS /usr/include)
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
