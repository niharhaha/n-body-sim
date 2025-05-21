#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Constants.h"


class Particle {

public:
    Particle(float mass = UNIT_MASS, sf::Vector2f position = WINDOW_CENTER, sf::Vector2f velocity = ZERO_VELOCITY, float radius = UNIT_RADIUS, sf::Color color = DEF_COLOR);

    // Getters
    float getMass() const { return mass_; }
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
    void draw(sf::RenderWindow& window) const { window.draw(shape_); }

private:
    float mass_;
    sf::Vector2f position_;
    sf::Vector2f velocity_;
    sf::CircleShape shape_;
};

#endif // PARTICLE_H
