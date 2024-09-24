#include "brute_force_solver.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>

template<typename T, typename Result>
BruteForceSolver<T, Result>::BruteForceSolver(
    const std::vector<T>& domain, 
    size_t maxDepth,
    std::function<bool(const std::vector<T>&)> constraintCheck,
    std::function<Result(const std::vector<T>&)> objectiveFunction,
    bool useParallelProcessing,
    size_t numThreads)
    : domain(domain), maxDepth(maxDepth), constraintCheck(constraintCheck),
      objectiveFunction(objectiveFunction), useParallelProcessing(useParallelProcessing),
      numThreads(numThreads) {}

template<typename T, typename Result>
Result BruteForceSolver<T, Result>::solve() {
    return useParallelProcessing ? solveParallel() : solveSequential();
}

template<typename T, typename Result>
Result BruteForceSolver<T, Result>::solveSequential() {
    std::vector<T> current;
    Result bestResult = Result();
    auto startTime = std::chrono::high_resolution_clock::now();

    backtrack(current, bestResult);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Sequential execution time: " << duration.count() << " ms" << std::endl;

    return bestResult;
}

template<typename T, typename Result>
Result BruteForceSolver<T, Result>::solveParallel() {
    std::vector<std::future<Result>> futures;
    Result bestResult = Result();
    auto startTime = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < numThreads; ++i) {
        futures.push_back(std::async(std::launch::async, [this, i]() {
            std::vector<T> current;
            Result localBestResult = Result();
            backtrackParallel(current, localBestResult, i);
            return localBestResult;
        }));
    }

    for (auto& future : futures) {
        Result threadResult = future.get();
        if (threadResult > bestResult) {
            bestResult = threadResult;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Parallel execution time: " << duration.count() << " ms" << std::endl;

    return bestResult;
}

template<typename T, typename Result>
void BruteForceSolver<T, Result>::backtrack(std::vector<T>& current, Result& bestResult) {
    if (current.size() == maxDepth) {
        if (constraintCheck(current)) {
            Result result = objectiveFunction(current);
            if (result > bestResult) {
                bestResult = result;
            }
        }
        return;
    }

    for (const T& item : domain) {
        current.push_back(item);
        backtrack(current, bestResult);
        current.pop_back();
    }
}

template<typename T, typename Result>
void BruteForceSolver<T, Result>::backtrackParallel(std::vector<T>& current, Result& bestResult, size_t threadId) {
    if (current.size() == maxDepth) {
        if (constraintCheck(current)) {
            Result result = objectiveFunction(current);
            if (result > bestResult) {
                bestResult = result;
            }
        }
        return;
    }

    for (size_t i = threadId; i < domain.size(); i += numThreads) {
        current.push_back(domain[i]);
        backtrackParallel(current, bestResult, threadId);
        current.pop_back();
    }
}
