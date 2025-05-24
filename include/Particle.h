#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Constants.h"

class Particle {

public:
    // Constructor
    Particle(float mass = UNIT_MASS, sf::Vector2f position = WINDOW_CENTER, sf::Vector2f velocity = ZERO_VEC, 
        float radius = UNIT_RADIUS, sf::Color color = DEF_COLOR) : mass_(mass), position_(position), velocity_(velocity), shape_(radius) {
        if (color == sf::Color::Black) { color = getColorFromMass(mass); }
        shape_.setFillColor(color);
        shape_.setOrigin({radius, radius}); 
        shape_.setPosition(position_);
        if (radius >= 5) { shape_.setOutlineThickness(std::log(radius) / 1.4); };
    }

    // Getters
    float getMass() const { return mass_; }
    float getRadius() const { return shape_.getRadius(); }
    sf::Vector2f getPosition() const { return position_; }
    sf::Vector2f getVelocity() const { return velocity_; }

    // Setters
    void setMass(float mass) { mass_ = mass; }
    void setPosition(const sf::Vector2f& pos) { position_ = pos; shape_.setPosition(pos); }
    void setVelocity(const sf::Vector2f& vel) { velocity_ = vel; }

    /* Update position based on velocity and timestep (dt)
    x_f = x_i + v * dt */
    void updatePosition(float dt) { setPosition(position_ + velocity_ * dt); }

    /* Apply force for timestep (dt) to update velocity
    F = m * a --> a = F / m
    v_f = v_i + a * dt = v_i + F / m * dt */
    void applyForce(const sf::Vector2f& force, float dt) { velocity_ += (force / mass_) * dt; }

    // Draw to a SFML window
    void draw(sf::RenderWindow& window) const { if (SCREEN.contains(shape_.getPosition())) window.draw(shape_); }

    // Compute force exerted by p2 on p1
    static inline sf::Vector2f computeForce(const Particle& p1, const Particle& p2) {
        sf::Vector2f dir = p2.getPosition() - p1.getPosition();
        float distSq = dir.x * dir.x + dir.y * dir.y; 
        if (distSq == 0) { return {0.f, 0.f}; } // To avoid division by zero; TODO: implement collision so this is never the case
        float dist = std::sqrt(distSq);
        float forceMag = G * p1.getMass() * p2.getMass() / distSq;
            
        return forceMag * (dir / dist);
    }

    // Assign color to mass to particle based on how heavy it is
    static sf::Color getColorFromMass(float mass) {
        if (mass > 1e18f) { return sf::Color(40, 40, 120); } // Extremely large bodies
        if (mass > 1e15f) { return sf::Color(120, 100, 220); }

        const float minMass = 0.1f;       
        const float maxMass = 1e14f;   

        std::vector<sf::Color> colorScale = {
            sf::Color(220, 220, 255),  // Pale blue
            sf::Color(150, 200, 255),  // Sky blue
            sf::Color(100, 220, 255),  // Cyan
            sf::Color(100, 255, 200),  // Teal
            sf::Color(180, 150, 255),  // Lavender
            sf::Color(120, 100, 220),  // Violet
            sf::Color(40, 40, 120)     // Deep blue/near-black
        };

        float logMass = std::log10(std::clamp(mass, minMass, maxMass));
        float logMin = std::log10(minMass);
        float logMax = std::log10(maxMass);
        
        float t = (logMass - logMin) / (logMax - logMin); // Normalize [0, 1]

        int r = static_cast<int>(255 * std::clamp(3 * t - 1.5f, 0.f, 1.f));
        int g = static_cast<int>(255 * std::clamp(3 - 3 * t, 0.f, 1.f));
        int b = static_cast<int>(255 * std::clamp(1.5f - std::abs(3 * t - 1.5f), 0.f, 1.f));

        return sf::Color(r, g, b);
}

private:
    float mass_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
};

#endif 
