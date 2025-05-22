#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Forces.h"
#include <iostream>

void benchmarkBarnesHut(int size = 10000, int iters = 2000);
void benchmarkBruteForce(int size = 1000, int iters = 1000);

int main() {
    benchmarkBarnesHut(10000, 1000);
    benchmarkBruteForce(1000, 1000);
    return 0;
}
