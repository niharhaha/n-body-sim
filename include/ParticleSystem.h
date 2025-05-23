#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <vector>
#include "Particle.h"
#include <SFML/System/Vector2.hpp>

class ParticleSystem {

public:
    ParticleSystem() {};
    ParticleSystem(std::vector<Particle> particles);
    void addParticle(float mass = UNIT_MASS, sf::Vector2f position = WINDOW_CENTER, sf::Vector2f velocity = ZERO_VEC, float radius = UNIT_RADIUS, sf::Color color = DEF_COLOR) { particles_.emplace_back(mass, position, velocity, radius, color); forces_.push_back({0, 0}); }
    void addParticle(const Particle& p) { particles_.push_back(p); forces_.push_back({0, 0});}
    void updateAndDraw(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    std::vector<Particle>& getParticles() { return particles_; } 
    std::vector<sf::Vector2f>& getForces() { return forces_; } 
    int getSize() { return particles_.size(); } 

    void createTriangularSystem(float sideLength = 100.f, float mass = UNIT_MASS, float radius = UNIT_RADIUS);
    void createRandomSystem(float size = 100, float minMass = 0.1f,float maxMass = 1e14f, float massSkew = 14.f, float minRadius = 0.05f, float maxRadius = 5.f);
    void createSolarSystem();
    void clearSystem() { particles_.clear(); forces_.clear(); };

private:
    std::vector<Particle> particles_;
    std::vector<sf::Vector2f> forces_;
};

#endif // PARTICLE_SYSTEM_H
