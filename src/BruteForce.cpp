#include "BruteForce.h"
#include "Constants.h" 
#include <cmath>

std::vector<sf::Vector2f> computeBruteForces(const std::vector<Particle> &particles) {
    size_t n = particles.size();

    std::vector<sf::Vector2f> forces(n, {0, 0});

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {

            sf::Vector2f dir = particles[j].getPosition() - particles[i].getPosition();
            float distSq = dir.x * dir.x + dir.y * dir.y; 
            if (distSq == 0) { distSq = 1e-11f; } // To avoid division by zero; TODO: implement collision so this is never the case
            float dist = std::sqrt(distSq);
            float forceMag = G * particles[i].getMass() * particles[j].getMass() / distSq;
                
            sf::Vector2f force = forceMag * dir / dist;
            
            forces[i] += force;
            forces[j] -= force;
        }
    }

    return forces;
}
