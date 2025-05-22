#include "Forces.h"
#include "Constants.h" 
#include <cmath>
#include <iostream>
#include <future>

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
    // sf::Clock timer;
    QuadTree quadTree(particles);
    quadTree.updateMassDistribution();

    // sf::Time elapsed = timer.getElapsedTime();
    // std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";

    std::vector<sf::Vector2f> forces(n, {0, 0});

    // sf::Clock timer2;
    
    for (size_t i = 0; i < n; i++) {
        forces[i] = quadTree.computeForceOnTarget(particles[i]);
    }

    for (int i = 0; i < n; i++) {
        
    }
    // elapsed = timer2.getElapsedTime();
    // std::cout << "Compute forces time: " << elapsed.asMilliseconds() << " ms\n";
    return forces;
}

std::vector<sf::Vector2f> computeThreadedBarnesHutForces(const std::vector<Particle> &particles) {
    size_t n = particles.size();
    sf::Clock timer;
    QuadTree quadTree(particles);
    quadTree.updateMassDistribution();

    sf::Time elapsed = timer.getElapsedTime();
    std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";

    const int numTasks = std::thread::hardware_concurrency();
    size_t chunkSize = n / numTasks;

    std::vector<sf::Vector2f> forces(n, {0, 0});
    std::vector<std::future<void>> futures(numTasks);

    sf::Clock timer2;
    
    for (size_t t = 0; t < numTasks; t++) {
        futures[t] = std::async(std::launch::async, [&quadTree, &particles, &forces, &chunkSize, &numTasks, &n, t]() {
            size_t start = t * chunkSize;
            size_t end = (t == numTasks - 1) ? n : start + chunkSize;
            for (size_t i = start; i < end; i++) {
                forces[i] = quadTree.computeForceOnTarget(particles[i]);
            }
        });
    }

    elapsed = timer2.getElapsedTime();
    std::cout << "Compute forces time: " << elapsed.asMilliseconds() << " ms\n";
    return forces;
}

