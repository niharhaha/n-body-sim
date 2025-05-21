#include "BarnesHut.h"
#include <iostream>

std::vector<sf::Vector2f> computeBarnesHutForces(const std::vector<Particle> &particles) {
    size_t n = particles.size();
    sf::Clock timer;
    QuadTree quadTree(particles);
    quadTree.updateMassDistribution();

    sf::Time elapsed = timer.getElapsedTime();
    std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";


    std::vector<sf::Vector2f> forces(n, {0, 0});

    for (int i = 0; i < n; i++) {
        forces[i] = quadTree.computeForceOnTarget(particles[i]);
    }

    return forces;
}
