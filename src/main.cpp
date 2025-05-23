#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Forces.h"
#include <iostream>

void benchmarkBruteForceByIters(int totalSize = 2500, int largeBodyCount = 2, int iters = 100);
void benchmarkBarnesHutByIters(int totalSize = 10000, int largeBodyCount = 3, int iters = 500);
void benchmarkThreadedBarnesHutByIters(int totalSize = 25000, int largeBodyCount = 4, int iters = 500);

void benchmarkBruteForceByTime(int totalSize = 2500, int largeBodyCount = 2, int time = 20000);
void benchmarkBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);
void benchmarkThreadedBarnesHutByTime(int totalSize = 15000, int largeBodyCount = 3, int time = 20000);

int main(int argc, char* argv[]) {
    benchmarkBruteForceByIters();
    benchmarkBarnesHutByIters();
    benchmarkThreadedBarnesHutByIters();
    benchmarkBruteForceByTime();
    benchmarkBarnesHutByTime();
    benchmarkThreadedBarnesHutByTime();
    return 0;
}
