#include <iostream>

#if defined(WITH_CUDA)
#include <cudnn.h>
#elif defined(WITH_ROCM)
#include <miopen/miopen.h>
#endif

void checkDNN() {
#if defined(WITH_CUDA)
    cudnnHandle_t handle;
    cudnnStatus_t status = cudnnCreate(&handle);
    if (status != CUDNN_STATUS_SUCCESS) {
        std::cerr << "cuDNN initialization failed: " << cudnnGetErrorString(status) << std::endl;
        return;
    }

    int version = cudnnGetVersion();
    std::cout << "cuDNN version: " << version << std::endl;

    cudnnDestroy(handle);
#elif defined(WITH_ROCM)
    miopenHandle_t handle;
    miopenStatus_t status = miopenCreate(&handle);
    if (status != miopenStatusSuccess) {
        std::cerr << "MIOpen initialization failed: " << miopenGetErrorString(status) << std::endl;
        return;
    }
    size_t major, minor, patch;
    miopenGetVersion(&major, &minor, &patch);
    std::cout << "MIOpen version: " << major << "." << minor << "." << patch << std::endl;

    miopenDestroy(handle);
#endif
}
