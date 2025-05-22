#include "Forces.h"
#include "Constants.h" 
#include <cmath>
#include <iostream>

std::vector<sf::Vector2f> computeBruteForces(const std::vector<Particle> &particles) {
    size_t n = particles.size();

    std::vector<sf::Vector2f> forces(n, {0, 0});

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sf::Vector2f force = Particle::computeForce(particles[i], particles[j]);
            forces[i] += force;
            forces[j] -= force;
        }
    }

    return forces;
}

std::vector<sf::Vector2f> computeBarnesHutForces(const std::vector<Particle> &particles) {
    size_t n = particles.size();
    sf::Clock timer;
    QuadTree quadTree(particles);
    quadTree.updateMassDistribution();

    sf::Time elapsed = timer.getElapsedTime();
    // std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";


    std::vector<sf::Vector2f> forces(n, {0, 0});
    

    for (int i = 0; i < n; i++) {
        forces[i] = quadTree.computeForceOnTarget(particles[i]);
    }

    return forces;
}
