#include "Forces.h"
#include "Constants.h" 
#include <cmath>
#include <iostream>
#include <future>
#include "ThreadPool.h"

void computeBruteForces(ParticleSystem& ps) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();

    size_t n = particles.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sf::Vector2f force = Particle::computeForce(particles[i], particles[j]);
            forces[i] += force;
            forces[j] -= force;
        }
    }
}

void computeBarnesHutForces(ParticleSystem& ps) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();

    size_t n = particles.size();
    // sf::Clock timer;
    QuadTree quadTree(particles);
    quadTree.updateMassDistribution();

    // sf::Time elapsed = timer.getElapsedTime();
    // std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";


    // sf::Clock timer2;
    
    for (size_t i = 0; i < n; i++) {
        forces[i] = quadTree.computeForceOnTarget(particles[i]);
    }

    for (int i = 0; i < n; i++) {
        
    }
    // elapsed = timer2.getElapsedTime();
    // std::cout << "Compute forces time: " << elapsed.asMilliseconds() << " ms\n";
}


void computeThreadPoolBarnesHutForces(ParticleSystem& ps, ThreadPool& pool) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();

    size_t n = particles.size();

    int numThreads = std::thread::hardware_concurrency();
    size_t chunkSize = n / numThreads;


    sf::Clock timer;
    QuadTree quadTree(particles);
    sf::Time elapsed = timer.getElapsedTime();
    std::cout << "QuadTree build time: " << elapsed.asMilliseconds() << " ms\n";

    sf::Clock timer2;
    quadTree.updateMassDistribution();
    elapsed = timer2.getElapsedTime();
    std::cout << "Mass update time: " << elapsed.asMilliseconds() << " ms\n";
    
    std::vector<std::future<void>> futures(numThreads);

    for (size_t t = 0; t < numThreads; t++) {
        futures[t] = pool.enqueue([&quadTree, &particles, &forces, &chunkSize, &numThreads, &n, t] {
            size_t start = t * chunkSize;
            size_t end = (t == numThreads - 1) ? n : start + chunkSize;
            for (size_t i = start; i < end; i++) {
                forces[i] = quadTree.computeForceOnTarget(particles[i]);
            }
        });
    }

    for (auto& f : futures) { f.get(); }
}
