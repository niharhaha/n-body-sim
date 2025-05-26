#include "QuadTree.h"
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

QuadTree::QuadTree(const std::vector<Particle> &particles) {
    tree_.clear(); tree_.reserve(4 * particles.size()); // Ready tree_ vector
    tree_.emplace_back(Quad());
    for (const auto& particle : particles) {
        if (particle.isOutOfRange()) { continue; }
        else { insertParticle(particle); }
    }
    updateMassDistribution();
}

bool QuadTree::insertParticle(const Particle &p) {
    return insertParticle(0, p);
}

bool QuadTree::insertParticle(int idx, const Particle &p) {
    QuadTreeNode& node = tree_[idx];
    if (!node.containsPoint(p)) { return false; }
    
    if (!node.subdivided && !node.hasParticle) {    
        node.particle = const_cast<Particle*>(&p); 
        node.hasParticle = true; 
    } else {
        if (!node.subdivided) {
            subdivide(idx);
            // node = tree_[idx];
            for (int i = 0; i < 4; i++) {
                if (insertParticle(node.child_idx + i, *(node.particle))) { break; }
            }
            // node = tree_[idx];
            node.hasParticle = false;
        }
        for (int i = 0; i < 4; i++) {
            if (insertParticle(node.child_idx + i, p)) { break; }
        }
    }

    return true;
}

sf::Vector2f QuadTree::computeForceOnTarget(int idx, const Particle &target) {
    QuadTreeNode& node = tree_[idx];
    if (node.totalMass == 0.f) { return {0.f, 0.f}; } // If no particle/mass exists

    if (!node.subdivided && node.hasParticle) { // Single particle at node        
        return Particle::computeForce(target, *(node.particle));
    }  

    sf::Vector2f dir = node.centerOfMass - target.getPosition();
    float distSq = dir.x * dir.x + dir.y * dir.y; 
    if (distSq < EPSILON) { return {0.f, 0.f}; }
    float dist = std::sqrt(distSq);
    
    float ratio = std::max(node.region.width, node.region.height) / dist;

    if (ratio < THETA) { // If can approximate (Barnes-Hut)
        return G * target.getMass() * node.totalMass / distSq * (dir / dist);
    } else { // Else sum forces by children
        sf::Vector2f force = {0.f, 0.f};
        for (int i = 0; i < 4; ++i) {
            int child = node.child_idx + i;
            if (child < tree_.size()) {
                force += computeForceOnTarget(child, target);
            }
        }
        return force;
    }
    
}

sf::Vector2f QuadTree::computeForceOnTarget(const Particle &target) { 
    return computeForceOnTarget(0, target);
}


void QuadTree::updateMassDistribution(int idx) {
    QuadTreeNode& node = tree_[idx];
    if (node.isLeaf()) { // If single particle
        if (node.hasParticle) {
            node.totalMass = node.particle->getMass();
            node.centerOfMass = node.particle->getPosition();
        }
        return;
    }
    
    sf::Vector2f centerOfMass = {0.f, 0.f};
    float totalMass = 0.f;

    // Sum children mass and position

    for (int i = 0; i < 4 && node.child_idx != 0; i++) {
        updateMassDistribution(node.child_idx + i);
        QuadTreeNode& child = tree_[node.child_idx + i];
        totalMass += child.totalMass;
        centerOfMass += child.centerOfMass * child.totalMass;
    }
    // At least one child exists
    node.totalMass = totalMass;
    if (totalMass > 0) { node.centerOfMass = centerOfMass / totalMass; }
}

void QuadTree::updateMassDistribution() {
    updateMassDistribution(0);
}

void QuadTree::subdivide(int idx) {
    QuadTreeNode& node = tree_[idx];
    node.subdivided = true;

    float hw = node.region.width / 2.f;
    float hh = node.region.height / 2.f;

    sf::Vector2f center = node.region.origin;
    int childStart = tree_.size();

    std::array<sf::Vector2f, 4> centers = {
        sf::Vector2f(center.x + hw / 2.f, center.y - hh / 2.f), // NE
        sf::Vector2f(center.x - hw / 2.f, center.y - hh / 2.f), // NW
        sf::Vector2f(center.x - hw / 2.f, center.y + hh / 2.f), // SW
        sf::Vector2f(center.x + hw / 2.f, center.y + hh / 2.f)  // SE
    };

    for (int i = 0; i < 4; ++i) {
        Quad childRegion{centers[i], hw, hh};
        tree_.push_back(QuadTreeNode(childRegion)); 
    }
    tree_[idx].child_idx = childStart;  
}


