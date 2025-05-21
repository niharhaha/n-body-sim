#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include "Particle.h"
#include "BruteForce.h"

class ParticleSystem {

public:
    ParticleSystem() {};
    ParticleSystem(std::vector<Particle> particles) : particles_(particles) {}
    void addParticle(float mass = UNIT_MASS, sf::Vector2f position = WINDOW_CENTER, sf::Vector2f velocity = ZERO_VEC, float radius = UNIT_RADIUS, sf::Color color = DEF_COLOR) { particles_.emplace_back(mass, position, velocity, radius, color); }
    void addParticle(const Particle& p) { particles_.push_back(p); }
    void updateAndDraw(sf::RenderWindow& window);
    void updateAndDraw(sf::RenderWindow& window, const std::vector<sf::Vector2f>& forces);
    std::vector<Particle>& getParticles() { return particles_; } 

    void createTriangularSystem(float sideLength = 100.f, float mass = UNIT_MASS, float radius = UNIT_RADIUS);
    void createRandomSystem(float size = 100, float mass = 0, float radius = UNIT_RADIUS);
    void createSolarSystem();

private:
    std::vector<Particle> particles_;
};

#endif // PARTICLE_SYSTEM_H
