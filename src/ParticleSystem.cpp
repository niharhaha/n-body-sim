#include "ParticleSystem.h"
#include <random>

ParticleSystem::ParticleSystem(std::vector<Particle> particles) {
    forces_.assign(particles.size(), sf::Vector2f{0.f, 0.f});
}

void ParticleSystem::updateAndDraw(sf::RenderWindow &window) {
    size_t n = particles_.size();
    int outSize = 0;
    // Apply forces to particles, update their position and draw them
    for (size_t i = 0; i < n; ++i) {
        if (particles_[i].isOutOfRange()) { outSize++; continue; }
        particles_[i].applyForce(forces_[i], TIME_STEP);
        sf::Vector2f newPos = particles_[i].updatePosition(TIME_STEP);

        if (!RANGE.contains(newPos)) {
            particles_[i].setOutOfRange();
        } else {
            if (SCREEN.contains(newPos)) { particles_[i].draw(window); };
        }
    }
    if (outSize > std::pow(6, std::log10(particles_.size()))) {
        particles_.erase(
        std::remove_if(particles_.begin(), particles_.end(),
            [](const Particle& p) { return p.isOutOfRange(); }),
        particles_.end());

        forces_.assign(particles_.size(), sf::Vector2f{0.f, 0.f});
    }
    
}

void ParticleSystem::createTriangularSystem(float sideLength, float mass, float radius) {
    clearSystem();

    // Calculate height of equilateral triangle
    float height = sideLength * std::sqrt(3.f) / 2.f;

    // Positions of the 3 vertices of an equilateral triangle centered roughly at center
    sf::Vector2f p1 = WINDOW_CENTER + sf::Vector2f(-sideLength / 2.f, height / 3.f);
    sf::Vector2f p2 = WINDOW_CENTER + sf::Vector2f(sideLength / 2.f, height / 3.f);
    sf::Vector2f p3 = WINDOW_CENTER + sf::Vector2f(0.f, -2.f * height / 3.f);

    // Add particles at these positions, stationary initially
    addParticle(mass, p1, ZERO_VEC, radius);
    addParticle(mass, p2, ZERO_VEC, radius);
    addParticle(mass, p3, ZERO_VEC, radius);
}

void ParticleSystem::createRandomSystem(float size, float minMass, float maxMass, float massSkew, float minRadius, float maxRadius) {
    std::random_device rd; std::mt19937 mt(rd());

    // Random distributions
    std::uniform_real_distribution<float> distX(0.f, WINDOW_WIDTH);
    std::uniform_real_distribution<float> distY(0.f, WINDOW_HEIGHT);
    std::uniform_real_distribution<float> distMass(0.f, 1.f);   
    std::uniform_real_distribution<float> distRadius(minRadius, maxRadius);  
    std::uniform_real_distribution<float> velX(WINDOW_WIDTH / -10, WINDOW_WIDTH / 10);
    std::uniform_real_distribution<float> velY(WINDOW_HEIGHT / -10, WINDOW_HEIGHT / 10);

    for (int i = 0; i < size; i++) {
        sf::Vector2f pos(distX(mt), distY(mt));
        sf::Vector2f vel(velX(mt) / 10, velY(mt) / 10);
        float u = distMass(mt);    
        float skewed = std::pow(u, massSkew); // left skew
        float mass = minMass + (maxMass - minMass) * skewed; // scale to range
        addParticle(mass, pos, vel, distRadius(mt));
    }
}
