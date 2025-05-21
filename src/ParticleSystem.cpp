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
    std::uniform_real_distribution<float> distMass(0.f, 1.f);   
    float skew = 1.f; 
    float minMass = 0.5f;
    float maxMass = 1e14f;

    std::uniform_real_distribution<float> distRadius(0.01f, 1.f);  

     for (int i = 0; i < size; i++) {
        sf::Vector2f pos(distX(mt), distY(mt));
        float u = distMass(mt);       // uniform [0,1]
        float skewed = std::pow(u, skew); // left skew
        // Scale to range:
        float mass = minMass + (maxMass - minMass) * skewed;

        particles_.emplace_back(mass, pos, ZERO_VEC, distRadius(mt));
    }
}

void ParticleSystem::createSolarSystem() {
    particles_.clear();

    particles_.emplace_back(
        1.989e30f * SCALE,                          // mass (Sun)
        WINDOW_CENTER,            // position
        sf::Vector2f(0.f, 0.f),            // velocity
        20.f,                              // radius (for drawing)
        sf::Color::Yellow                   // color
    );

    particles_.emplace_back(
        5.972e24f * SCALE,
        WINDOW_CENTER + sf::Vector2f(AU * SCALE, 0.f),
        sf::Vector2f(0.f, 29.78e3f * SCALE),
        10.f,
        sf::Color::Blue
    );

    

}
