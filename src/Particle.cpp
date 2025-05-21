#include "Particle.h"

Particle::Particle(float mass, sf::Vector2f position, sf::Vector2f velocity, float radius, sf::Color color)
    : mass_(mass), position_(position), velocity_(velocity), shape_(radius) {
    shape_.setFillColor(color);
    shape_.setOrigin({radius, radius}); // center the circle
    shape_.setPosition(position_);
}

