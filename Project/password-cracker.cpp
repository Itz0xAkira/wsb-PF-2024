#include "password_cracker.hpp"
#include <algorithm>

PasswordCracker::PasswordCracker(const std::string& charset, size_t maxLength, bool useParallelProcessing)
    : charset(charset), maxLength(maxLength),
      solver(std::vector<char>(charset.begin(), charset.end()), maxLength, 
             constraintCheck, objectiveFunction, useParallelProcessing) {}

std::string PasswordCracker::crackPassword(const std::function<bool(const std::string&)>& verifier) {
    auto result = solver.solve();
    if (result > 0) {
        std::string password(result, ' ');
        for (int i = result - 1, j = 0; i >= 0; --i, ++j) {
            password[j] = charset[i % charset.size()];
            i /= charset.size();
        }
        if (verifier(password)) {
            return password;
        }
    }
    return "";  // Password not found
}

bool PasswordCracker::constraintCheck(const std::vector<char>& solution) {
    return true;  // All combinations are valid
}

int PasswordCracker::objectiveFunction(const std::vector<char>& solution) {
    return solution.size();  // Prioritize longer passwords
}
