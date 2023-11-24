#include <iostream>
#include <stdexcept>

void processNumber(int num) {
    try {
        if (num == 0) {
            throw std::runtime_error("Cannot process with zero.");
        }

        int result = 10 / num;
        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown exception caught." << std::endl;
    }
}

int main() {
    try {
        processNumber(2);
        processNumber(0); // Òý·¢Òì³£
        processNumber(5);
    }
    catch (const std::exception& e) {
        std::cerr << "Main function caught an exception: " << e.what() << std::endl;
    }

    return 0;
}