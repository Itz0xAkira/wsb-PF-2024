# Brute Fource  Project Report

## Table of Contents
1. [Introduction](#introduction)
2. [Project Structure](#project-structure)
3. [Core Components](#core-components)
   3.1 [BruteForceSolver](#bruteforcesolver)
   3.2 [PasswordCracker](#passwordcracker)
4. [Implementation Details](#implementation-details)
   4.1 [BruteForceSolver](#bruteforcesolver-implementation)
   4.2 [PasswordCracker](#passwordcracker-implementation)
5. [Key Features](#key-features)
6. [Usage Guide](#usage-guide)
7. [Performance Considerations](#performance-considerations)
8. [Testing](#testing)
9. [Ethical Considerations](#ethical-considerations)
10. [Conclusion](#conclusion)

## 1. Introduction

This report details the implementation of a Password Cracker project, which utilizes a brute-force approach to attempt to discover passwords. The project is built upon a generic BruteForceSolver class, which has been specialized for the task of password cracking. This implementation serves as a demonstration of brute-force techniques and should be used responsibly and ethically.

## 2. Project Structure

The project is organized into several files:

1. `brute_force_solver.hpp`: Header file for the BruteForceSolver class
2. `brute_force_solver.cpp`: Implementation of the BruteForceSolver class
3. `password_cracker.hpp`: Header file for the PasswordCracker class
4. `password_cracker.cpp`: Implementation of the PasswordCracker class
5. `main.cpp`: Example usage of the PasswordCracker
6. `tests.cpp`: Unit tests for the PasswordCracker

This structure allows for clear separation of concerns and modularity, making the code easier to maintain and extend.

## 3. Core Components

### 3.1 BruteForceSolver

The BruteForceSolver is a template class that implements a generic brute-force algorithm. It is designed to be flexible and can be applied to various problems that require exhaustive search.

Key features:
- Template-based design for flexibility
- Support for custom constraint checks and objective functions
- Optional parallel processing for improved performance

### 3.2 PasswordCracker

The PasswordCracker class is built on top of the BruteForceSolver and specializes it for the task of password cracking. It provides a user-friendly interface for attempting to crack passwords using a brute-force approach.

Key features:
- Customizable character set for password generation
- Adjustable maximum password length
- Option for parallel processing
- Use of a verifier function for password checking

## 4. Implementation Details

### 4.1 BruteForceSolver

The BruteForceSolver class is implemented as follows:

```cpp
template<typename T, typename Result>
class BruteForceSolver {
public:
    BruteForceSolver(const std::vector<T>& domain, 
                     size_t maxDepth,
                     std::function<bool(const std::vector<T>&)> constraintCheck,
                     std::function<Result(const std::vector<T>&)> objectiveFunction,
                     bool useParallelProcessing = false,
                     size_t numThreads = std::thread::hardware_concurrency());

    Result solve();

private:
    // ... (private members and methods)
};
```

The solver uses recursive backtracking to generate all possible combinations up to the specified maximum depth. It can operate in either sequential or parallel mode, with the parallel mode utilizing multiple threads to speed up the search process.

### 4.2 PasswordCracker

The PasswordCracker class is implemented as follows:

```cpp
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
```

The PasswordCracker uses the BruteForceSolver with characters as the domain type. It generates passwords of increasing length up to the specified maximum, using the provided character set. The cracking process continues until a password satisfying the verifier function is found or all possibilities are exhausted.

## 5. Key Features

1. **Flexible Character Set**: Users can specify the character set to use for password generation, allowing for more targeted cracking attempts.

2. **Adjustable Maximum Length**: The maximum password length can be set, limiting the search space.

3. **Parallel Processing**: Optional parallel processing can significantly speed up the cracking process on multi-core systems.

4. **Verifier Function**: Instead of checking against a known password, the cracker uses a verifier function. This makes it more realistic and allows for different types of password verification (e.g., hashed passwords).

5. **Performance Measurement**: The main function measures and reports the total execution time for cracking the password.

6. **Comprehensive Unit Tests**: The project includes a suite of unit tests covering various scenarios.

## 6. Usage Guide

To use the PasswordCracker:

1. Include the necessary headers:
   ```cpp
   #include "password_cracker.hpp"
   ```

2. Create a PasswordCracker instance:
   ```cpp
   std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
   size_t maxLength = 6;
   bool useParallelProcessing = true;
   PasswordCracker cracker(charset, maxLength, useParallelProcessing);
   ```

3. Define a verifier function:
   ```cpp
   std::string targetPassword = "Abc123";
   auto verifier = [&targetPassword](const std::string& password) {
       return password == targetPassword;
   };
   ```

4. Attempt to crack the password:
   ```cpp
   std::string crackedPassword = cracker.crackPassword(verifier);
   ```

5. Check the result:
   ```cpp
   if (!crackedPassword.empty()) {
       std::cout << "Password cracked: " << crackedPassword << std::endl;
   } else {
       std::cout << "Password not found within the given constraints." << std::endl;
   }
   ```

## 7. Performance Considerations

The performance of the password cracker depends on several factors:

1. **Character Set Size**: Larger character sets increase the search space and time required.
2. **Maximum Password Length**: Longer maximum lengths exponentially increase the search space.
3. **Parallel Processing**: Using parallel processing can significantly speed up the cracking process on multi-core systems.
4. **Verifier Function Efficiency**: The efficiency of the verifier function can impact overall performance, especially for large search spaces.

## 8. Testing

The project includes a comprehensive set of unit tests (in `tests.cpp`) using the Google Test framework. These tests cover various scenarios:

1. Cracking short passwords
2. Cracking mixed-case passwords
3. Cracking alphanumeric passwords
4. Handling cases where the password is not found
5. Testing parallel processing functionality

To run the tests, compile `tests.cpp` with the other project files (excluding `main.cpp`) and link against the Google Test library.

## 9. Ethical Considerations

It is crucial to emphasize that this password cracker is implemented for educational and demonstrative purposes only. Using such tools to attempt unauthorized access to systems or accounts is illegal and unethical. Always respect privacy and security guidelines when working with password-related tools and techniques.

## 10. Conclusion

The Password Cracker project demonstrates the implementation of a brute-force approach to password cracking using C++. It showcases object-oriented design, template metaprogramming, and parallel processing techniques. While the project serves as an educational tool, it also highlights the importance of using strong, complex passwords to resist such brute-force attacks.

This implementation provides a foundation that can be extended and optimized for more specific use cases or for tackling other problems that require exhaustive search algorithms.
