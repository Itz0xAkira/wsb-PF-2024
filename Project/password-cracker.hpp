#ifndef PASSWORD_CRACKER_HPP
#define PASSWORD_CRACKER_HPP

#include "brute_force_solver.hpp"
#include <string>
#include <vector>
#include <functional>

class PasswordCracker {
public:
    PasswordCracker(const std::string& charset, size_t maxLength, bool useParallelProcessing = false);
    std::string crackPassword(const std::function<bool(const std::string&)>& verifier);

private:
    BruteForceSolver<char, int> solver;
    std::string charset;
    size_t maxLength;

    static bool constraintCheck(const std::vector<char>& solution);
    static int objectiveFunction(const std::vector<char>& solution);
};

#endif // PASSWORD_CRACKER_HPP
