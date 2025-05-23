#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Forces.h"
#include <iostream>

void benchmarkBruteForceByIters(int totalSize = 1000, int largeBodyCount = 1, int iters = 1000);
void benchmarkBarnesHutByIters(int totalSize = 5000, int largeBodyCount = 2, int iters = 1000);
void benchmarkThreadedBarnesHutByIters(int totalSize = 25000, int largeBodyCount = 5, int iters = 1000);

void benchmarkBruteForceByTime(int totalSize = 1000, int largeBodyCount = 1, int time = 30000);
void benchmarkBarnesHutByTime(int totalSize = 5000, int largeBodyCount = 2, int time = 30000);
void benchmarkThreadedBarnesHutByTime(int totalSize = 25000, int largeBodyCount = 5, int time = 30000);

int main(int argc, char* argv[]) {

    if (argc == 1) {
        benchmarkThreadedBarnesHutByTime(25000, 5, 0);
    }
    return 0;
}
