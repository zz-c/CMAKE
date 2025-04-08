// main.cpp
#include <iostream>
#include <zlib.h>

int main() {
    const char* str = "Hello, zlib!11111111112222222222333333333344444444445555555555";
    uLong str_len = std::strlen(str) + 1;  // °üº¬ NULL ×Ö·û

    // Ñ¹Ëõ
    uLong compressed_len = compressBound(str_len);
    char* compressed = new char[compressed_len];

    int result = compress(reinterpret_cast<Bytef*>(compressed), &compressed_len, reinterpret_cast<const Bytef*>(str), str_len);

    if (result == Z_OK) {
        std::cout << "Compression successful! Compressed size: " << compressed_len << std::endl;
    }
    else {
        std::cout << "Compression failed!" << std::endl;
    }

    delete[] compressed;
    return 0;
}
