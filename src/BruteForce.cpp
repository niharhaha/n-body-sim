#include "BruteForce.h"
#include "Constants.h" 
#include <cmath>

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
