#include "Particle.h"
#include <cmath>

Particle::Particle(float mass, sf::Vector2f position, sf::Vector2f velocity, float radius, sf::Color color)
    : mass_(mass), position_(position), velocity_(velocity), shape_(radius) {
    if (color == sf::Color::Black) {
        color = getColorFromMass(mass);
    } else {
        color = color;
    }

    shape_.setFillColor(color);
    shape_.setOrigin({radius, radius}); // center the circle
    shape_.setPosition(position_);
    if (radius >= 5) {
        shape_.setOutlineColor(sf::Color::White);            
        shape_.setOutlineThickness(std::log(radius) / 1.4);  
    }
                        
}


inline sf::Vector2f computeForce(const Particle& p1, const Particle& p2) {
    sf::Vector2f dir = p2.getPosition() - p1.getPosition();
    float distSq = dir.x * dir.x + dir.y * dir.y; 
    if (distSq == 0) { return {0.f, 0.f}; } // To avoid division by zero; TODO: implement collision so this is never the case
    float dist = std::sqrt(distSq);
    float forceMag = (distSq != 0) ? G * p1.getMass() * p2.getMass() / distSq : 0;
        
    return forceMag * (dir / dist);
}


