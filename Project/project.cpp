#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include <future>
#include <algorithm>

template<typename T, typename Result>
class BruteForceSolver {
private:
    std::vector<T> domain;
    size_t maxDepth;
    std::function<bool(const std::vector<T>&)> constraintCheck;
    std::function<Result(const std::vector<T>&)> objectiveFunction;
    bool useParallelProcessing;
    size_t numThreads;

public:
    BruteForceSolver(const std::vector<T>& domain, 
                     size_t maxDepth,
                     std::function<bool(const std::vector<T>&)> constraintCheck,
                     std::function<Result(const std::vector<T>&)> objectiveFunction,
                     bool useParallelProcessing = false,
                     size_t numThreads = std::thread::hardware_concurrency())
        : domain(domain), maxDepth(maxDepth), constraintCheck(constraintCheck),
          objectiveFunction(objectiveFunction), useParallelProcessing(useParallelProcessing),
          numThreads(numThreads) {}

    Result solve() {
        if (useParallelProcessing) {
            return solveParallel();
        } else {
            return solveSequential();
        }
    }

private:
    Result solveSequential() {
        std::vector<T> current;
        Result bestResult = Result();
        auto startTime = std::chrono::high_resolution_clock::now();

        backtrack(current, bestResult);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Sequential execution time: " << duration.count() << " ms" << std::endl;

        return bestResult;
    }

    Result solveParallel() {
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

    void backtrack(std::vector<T>& current, Result& bestResult) {
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

    void backtrackParallel(std::vector<T>& current, Result& bestResult, size_t threadId) {
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
};

// Example usage
int main() {
    std::vector<int> domain = {1, 2, 3, 4, 5};
    size_t maxDepth = 3;

    auto constraintCheck = [](const std::vector<int>& solution) {
        return std::accumulate(solution.begin(), solution.end(), 0) <= 10;
    };

    auto objectiveFunction = [](const std::vector<int>& solution) {
        return std::accumulate(solution.begin(), solution.end(), 1, std::multiplies<int>());
    };

    BruteForceSolver<int, int> solver(domain, maxDepth, constraintCheck, objectiveFunction, true);
    int result = solver.solve();

    std::cout << "Best result: " << result << std::endl;

    return 0;
}
