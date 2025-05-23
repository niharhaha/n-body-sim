#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Forces.h"
#include <iostream>

void benchmarkBruteForceByIters(int totalSize = 1000, int largeBodyCount = 5, int iters = 2500);
void benchmarkBarnesHutByIters(int totalSize = 5000, int largeBodyCount = 5, int iters = 2500);
void benchmarkThreadedBarnesHutByIters(int totalSize = 50000, int largeBodyCount = 5, int iters = 2500);

void benchmarkBruteForceByTime(int totalSize = 1000, int largeBodyCount = 5, int time = 25000);
void benchmarkBarnesHutByTime(int totalSize = 5000, int largeBodyCount = 5, int time = 25000);
void benchmarkThreadedBarnesHutByTime(int totalSize = 50000, int largeBodyCount = 5, int time = 25000);

int main(int argc, char* argv[]) {
    benchmarkThreadedBarnesHutByIters();
    return 0;
}
