#ifndef BRUTE_FORCE_SOLVER_HPP
#define BRUTE_FORCE_SOLVER_HPP

#include <vector>
#include <functional>
#include <future>

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
    std::vector<T> domain;
    size_t maxDepth;
    std::function<bool(const std::vector<T>&)> constraintCheck;
    std::function<Result(const std::vector<T>&)> objectiveFunction;
    bool useParallelProcessing;
    size_t numThreads;

    Result solveSequential();
    Result solveParallel();
    void backtrack(std::vector<T>& current, Result& bestResult);
    void backtrackParallel(std::vector<T>& current, Result& bestResult, size_t threadId);
};

#include "brute_force_solver.cpp"  // Include the implementation for template class

#endif // BRUTE_FORCE_SOLVER_HPP
