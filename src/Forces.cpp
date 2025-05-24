#include "Forces.h"
#include <future>

void computeBruteForces(ParticleSystem& ps) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();
    size_t n = ps.getSize();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sf::Vector2f force = Particle::computeForce(particles[i], particles[j]);
            forces[i] += force;
            forces[j] -= force; // NLM 3: Every action has an opposite reaction
        }
    }
}

void computeBarnesHutForces(ParticleSystem& ps) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();
    size_t n = ps.getSize();

    QuadTree quadTree(particles); // Create a QuadTree to compute forces
    quadTree.updateMassDistribution();
    
    for (size_t i = 0; i < n; i++) {
        forces[i] = quadTree.computeForceOnTarget(particles[i]);
    }
}


void computeThreadPoolBarnesHutForces(ParticleSystem& ps, ThreadPool& pool) {
    const std::vector<Particle> &particles = ps.getParticles();
    std::vector<sf::Vector2f>& forces = ps.getForces();
    size_t n = ps.getSize();

    int numThreads = pool.getNumWorkers();
    size_t chunkSize = n / numThreads;

    QuadTree quadTree(particles); // Create a QuadTree to compute forces
    quadTree.updateMassDistribution();
    
    std::vector<std::future<void>> futures(numThreads);

    for (size_t t = 0; t < numThreads; t++) {
        // Evenly divide force calculations among 
        futures[t] = pool.enqueue([&quadTree, &particles, &forces, &chunkSize, &numThreads, &n, t] {
            size_t start = t * chunkSize;
            size_t end = (t == numThreads - 1) ? n : start + chunkSize;
            for (size_t i = start; i < end; i++) {
                forces[i] = quadTree.computeForceOnTarget(particles[i]);
            }
        });
    }

    for (auto& f : futures) { f.get(); } // Wait for force calculations to finish
}
