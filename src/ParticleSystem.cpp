#include "ParticleSystem.h"
#include <iostream>
#include <random>

void ParticleSystem::updateAndDraw(sf::RenderWindow &window) {    
    size_t n = particles_.size();
    // Apply forces to particles, update their position and draw them
    for (size_t i = 0; i < n; ++i) {
        particles_[i].updatePosition(TIME_STEP);
        particles_[i].draw(window);
    }
}

void ParticleSystem::updateAndDraw(sf::RenderWindow &window, const std::vector<sf::Vector2f> &forces) {    
    size_t n = particles_.size();
    // Apply forces to particles, update their position and draw them
    for (size_t i = 0; i < n; ++i) {
        sf::Vector2f force = forces[i];
        std::cout << "Force " << i << ": (" << force.x << ", " << force.y << ")\n";
        particles_[i].applyForce(forces[i], TIME_STEP);
        particles_[i].updatePosition(TIME_STEP);
        particles_[i].draw(window);
    }
}

void ParticleSystem::createTriangularSystem(float sideLength, float mass, float radius) {
    particles_.clear();

    // Calculate height of equilateral triangle
    float height = sideLength * std::sqrt(3.f) / 2.f;

    // Positions of the 3 vertices of an equilateral triangle centered roughly at center
    sf::Vector2f p1 = WINDOW_CENTER + sf::Vector2f(-sideLength / 2.f, height / 3.f);
    sf::Vector2f p2 = WINDOW_CENTER + sf::Vector2f(sideLength / 2.f, height / 3.f);
    sf::Vector2f p3 = WINDOW_CENTER + sf::Vector2f(0.f, -2.f * height / 3.f);

    // Add particles at these positions, stationary initially
    particles_.emplace_back(mass, p1, ZERO_VEC, radius);
    particles_.emplace_back(mass, p2, ZERO_VEC, radius);
    particles_.emplace_back(mass, p3, ZERO_VEC, radius);
}

void ParticleSystem::createRandomSystem(float size, float mass, float radius) {
    particles_.clear();

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<float> distX(0.f, WINDOW_WIDTH);
    std::uniform_real_distribution<float> distY(0.f, WINDOW_HEIGHT);
    std::uniform_real_distribution<float> distMass(0.5f, 1000.f);   
    std::uniform_real_distribution<float> distRadius(1.f, 14.f);  // example radius range

     for (int i = 0; i < size; i++) {
        sf::Vector2f pos(distX(mt), distY(mt));

        particles_.emplace_back(distMass(mt), pos, ZERO_VEC, distRadius(mt));
    }



}
