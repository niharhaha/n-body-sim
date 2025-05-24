#include "QuadTree.h"
#include <vector>
#include <thread>
#include <mutex>

QuadTree::QuadTree(const std::vector<Particle>& particles, const sf::FloatRect& boundary) : boundary_(boundary) {
    for (auto& particle : particles) { insertParticle(particle); }
}

bool QuadTree::insertParticle(const Particle &p) {
    if (!containsPoint(boundary_, p.getPosition())) { return false; }  // Don't insert out-of-range particles

    if (!subdivided_ && !hasParticle_) {
        particle_ = const_cast<Particle*>(&p); // Add particle to node if none exists
        hasParticle_ = true; 
    } else { 
        if (!subdivided_) { // Subdivide if not
            subdivide();
            for (auto& child : children_) { if (child->insertParticle(*particle_)) { break; } }
            hasParticle_ = false;
        }
        // Insert particle to appropriate child node
        for (auto& child : children_) { if (child->insertParticle(p)) { break; } } 
    }
    
    return true;
}


sf::Vector2f QuadTree::computeForceOnTarget(const Particle &target) {
    if (totalMass_ == 0.f) { return {0.f, 0.f}; } // If no particle/mass exists
    if (particle_ && particle_ == &target) { return {0.f, 0.f}; } // Particle doesn't exert force on itself

    if (!subdivided_ && particle_) { // Single particle at node
        return Particle::computeForce(target, *particle_);
    } else { 
        sf::Vector2f dir = centerOfMass_ - target.getPosition();
        float distSq = dir.x * dir.x + dir.y * dir.y; 
        if (distSq < EPSILON) { return {0.f, 0.f}; }
        float dist = std::sqrt(distSq);
        
        float ratio = std::max(boundary_.size.x, boundary_.size.y) / dist;

        if (ratio < THETA) { // If can approximate (Barnes-Hut)
            return G * target.getMass() * totalMass_ / distSq * (dir / dist);
        } else { // Else sum forces by children
            sf::Vector2f force = {0.f, 0.f};
            for (int i = 0; i < 4; ++i) {
                if (children_[i]) {
                    force += children_[i]->computeForceOnTarget(target);
                }
            }
            return force;
        }
    }
    
    return {0.f, 0.f};
}

void QuadTree::updateMassDistribution() {
    if (isLeaf()) { // If single particle
        if (hasParticle_) {
            totalMass_ = particle_->getMass();
            centerOfMass_ = particle_->getPosition();
        }
        return;
    }
    
    totalMass_ = 0.f;
    centerOfMass_ = {0.f, 0.f};
    // Sum children mass and position
    for (auto& child : children_) {
        if (child) {
            child->updateMassDistribution();
            totalMass_ += child->totalMass_;
            centerOfMass_ += child->centerOfMass_ * child->totalMass_;
        }
    }

    // At least one child exists
    if (totalMass_ > 0) { centerOfMass_ /= totalMass_; }
}

void QuadTree::subdivide() {
    subdivided_ = true;

    sf::Vector2f boundaryPos = boundary_.position;
    sf::Vector2f boundarySize = boundary_.size;

    float halfWidth = boundarySize.x / 2.f;
    float halfHeight = boundarySize.y / 2.f;

    children_[0] = std::make_unique<QuadTree>(sf::FloatRect({boundaryPos.x + halfWidth, boundaryPos.y}, {halfWidth, halfHeight})); // NE
    children_[1] = std::make_unique<QuadTree>(sf::FloatRect({boundaryPos.x, boundaryPos.y}, {halfWidth, halfHeight})); // NW
    children_[2] = std::make_unique<QuadTree>(sf::FloatRect({boundaryPos.x, boundaryPos.y + halfHeight}, {halfWidth, halfHeight})); // SW
    children_[3] = std::make_unique<QuadTree>(sf::FloatRect({boundaryPos.x + halfWidth, boundaryPos.y + halfHeight}, {halfWidth, halfHeight})); // SE
}
