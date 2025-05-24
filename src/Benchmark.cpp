#include "ParticleSystem.h"
#include "Forces.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ThreadPool.h"
#include "Simulation.h"

// Generic benchmark simulation runner
template <typename Simulator, typename Func, typename... Args>
void benchmark(Simulator simRunner, Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int simStat, std::string algoName) {
    ParticleSystem ps;
    ps.createRandomSystem(totalSize - largeBodyCount);   
    ps.createRandomSystem(largeBodyCount - 1, 1e16f, 1e17f, 7.f, 10.f, 15.f);  
    if (largeBodyCount > 0) { ps.createRandomSystem(1, 1e18f, 1e21f, 14.f, 20.f, 25.f); } 

    simRunner(ps, [forceComputor, &args...](ParticleSystem& ps_ref) { forceComputor(ps_ref, std::forward<Args>(args)...); }, simStat, algoName);
}

// Generic iterations benchmark simulation runner
template <typename Func, typename... Args>
void benchmarkByIters(Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int iters, std::string algoName) {
    benchmark([](ParticleSystem& ps, auto&& func, int iters, std::string algoName) { createIterSimulation(ps, std::forward<decltype(func)>(func), iters, algoName);},
    forceComputor, args..., totalSize, largeBodyCount, iters, algoName);
}

// Generic timer benchmark simulation runner
template <typename Func, typename... Args>
void benchmarkByTime(Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int time, std::string algoName) {
    benchmark([](ParticleSystem& ps, auto&& func, int time, std::string algoName) { createTimeSimulation(ps, std::forward<decltype(func)>(func), time, algoName);},
    forceComputor, args..., totalSize, largeBodyCount, time, algoName);
}

// Benchmarking functions base on type, mode
void benchmarkThreadedBarnesHutByIters(int totalSize, int largeBodyCount, int iters) {
    ThreadPool pool;
    std::ostringstream oss;
    oss << "Threaded(" << pool.getNumWorkers() << ") Barnes Hut";
    benchmarkByIters([&pool](ParticleSystem& ps_ref) { computeThreadPoolBarnesHutForces(ps_ref, pool); }, totalSize, largeBodyCount, iters, oss.str());
}

void benchmarkBarnesHutByIters(int totalSize, int largeBodyCount, int iters) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBarnesHutForces(ps_ref); }, totalSize, largeBodyCount, iters, "Barnes Hut");
}

void benchmarkBruteForceByIters(int totalSize, int largeBodyCount, int iters) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBruteForces(ps_ref); }, totalSize, largeBodyCount, iters, "Brute Force");
}

void benchmarkThreadedBarnesHutByTime(int totalSize, int largeBodyCount, int time) {
    ThreadPool pool;
    std::ostringstream oss;
    oss << "Threaded(" << pool.getNumWorkers() << ") Barnes Hut";
    benchmarkByTime([&pool](ParticleSystem& ps_ref) { computeThreadPoolBarnesHutForces(ps_ref, pool); }, totalSize, largeBodyCount, time, oss.str());
}

void benchmarkBarnesHutByTime(int totalSize, int largeBodyCount, int time) {
    benchmarkByTime([](ParticleSystem& ps_ref) { computeBarnesHutForces(ps_ref); }, totalSize, largeBodyCount, time, "Barnes Hut");
}

void benchmarkBruteForceByTime(int totalSize, int largeBodyCount, int time) {
    benchmarkByTime([](ParticleSystem& ps_ref) { computeBruteForces(ps_ref); }, totalSize, largeBodyCount, time, "Brute Force");
}