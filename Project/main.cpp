#include "password_cracker.hpp"
#include <iostream>
#include <chrono>

int main() {
    std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t maxLength = 6;
    bool useParallelProcessing = true;

    PasswordCracker cracker(charset, maxLength, useParallelProcessing);

    std::string targetPassword = "Abc123";
    auto verifier = [&targetPassword](const std::string& password) {
        return password == targetPassword;
    };

    auto startTime = std::chrono::high_resolution_clock::now();
    std::string crackedPassword = cracker.crackPassword(verifier);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    if (!crackedPassword.empty()) {
        std::cout << "Password cracked: " << crackedPassword << std::endl;
    } else {
        std::cout << "Password not found within the given constraints." << std::endl;
    }

    std::cout << "Total execution time: " << duration.count() << " ms" << std::endl;

    return 0;
}
