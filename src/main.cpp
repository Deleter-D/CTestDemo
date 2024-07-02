#include <iostream>
#include <cstdlib>
#include <cmath>

// Forward declaration of function in dnn_test.cpp
void checkDNN();

int main() {
    const char* ld_library_path = std::getenv("LD_LIBRARY_PATH");
    if (ld_library_path != nullptr) {
        std::cout << "LD_LIBRARY_PATH: " << ld_library_path << std::endl;
    } else {
        std::cout << "LD_LIBRARY_PATH is not set." << std::endl;
    }

    // Use a function from the math library to ensure it is linked correctly
    double result = sqrt(16.0);
    std::cout << "sqrt(16.0) = " << result << std::endl;
    
    // Call the function to check DNN
    checkDNN();

    return 0;
}
