#include "ParticleSystem.h"
#include "Forces.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ThreadPool.h"
#include "Simulation.h"


template <typename Simulator, typename Func, typename... Args>
void benchmark(Simulator simRunner, Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int simStat) {
    ParticleSystem ps;
    ps.createRandomSystem(totalSize - largeBodyCount);   
    ps.createRandomSystem(largeBodyCount, 1e15f, 1e17f, 2.f, 10.f, 15.f);   

    simRunner(ps, [forceComputor, &args...](ParticleSystem& ps_ref) { forceComputor(ps_ref, std::forward<Args>(args)...); }, simStat);
}

template <typename Func, typename... Args>
void benchmarkByIters(Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int iters) {
    benchmark([](ParticleSystem& ps, auto&& func, int iters) { createIterSimulation(ps, std::forward<decltype(func)>(func), iters);},
    forceComputor, args..., totalSize, largeBodyCount, iters);
}

template <typename Func, typename... Args>
void benchmarkByTime(Func forceComputor, Args&&... args, int totalSize, int largeBodyCount, int time) {
    benchmark([](ParticleSystem& ps, auto&& func, int time) { createTimeSimulation(ps, std::forward<decltype(func)>(func), time);},
    forceComputor, args..., totalSize, largeBodyCount, time);
}

void benchmarkThreadedBarnesHutByIters(int totalSize, int largeBodyCount, int iters) {
    ThreadPool pool;
    benchmarkByIters([&pool](ParticleSystem& ps_ref) { computeThreadPoolBarnesHutForces(ps_ref, pool); }, totalSize, largeBodyCount, iters);
}

void benchmarkBarnesHutByIters(int totalSize, int largeBodyCount, int iters) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBarnesHutForces(ps_ref); }, totalSize, largeBodyCount, iters);
}

void benchmarkBruteForceByIters(int totalSize, int largeBodyCount, int iters) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBruteForces(ps_ref); }, totalSize, largeBodyCount, iters);
}

void benchmarkThreadedBarnesHutByTime(int totalSize, int largeBodyCount, int time) {
    ThreadPool pool;
    benchmarkByIters([&pool](ParticleSystem& ps_ref) { computeThreadPoolBarnesHutForces(ps_ref, pool); }, totalSize, largeBodyCount, time);
}

void benchmarkBarnesHutByTime(int totalSize, int largeBodyCount, int time) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBarnesHutForces(ps_ref); }, totalSize, largeBodyCount, time);
}

void benchmarkBruteForceByTime(int totalSize, int largeBodyCount, int time) {
    benchmarkByIters([](ParticleSystem& ps_ref) { computeBruteForces(ps_ref); }, totalSize, largeBodyCount, time);
}