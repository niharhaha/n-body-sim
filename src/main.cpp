#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "Forces.h"
#include <iostream>

void benchmarkBarnesHut(int size = 100000, int iters = 2000);

int main() {
    benchmarkBarnesHut();
    return 0;
}
