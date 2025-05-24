#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "Particle.h"
#include <memory>

class QuadTree {
public:
    // Constructors
    QuadTree(const sf::FloatRect& boundary = SCREEN) : boundary_(boundary), particle_(0) {};
    QuadTree(const std::vector<Particle>& particles, const sf::FloatRect& boundary = SCREEN);

    bool insertParticle(const Particle& p); // Add particle to QuadTree
    void updateMassDistribution(); // Propogate QuadTree mass
    sf::Vector2f computeForceOnTarget(const Particle& target); // Use QuadTree to compute mass on particle

private:
    sf::FloatRect boundary_;  // Region covered by this node
    Particle* particle_ = nullptr; // Stores a particle for leaf nodes
    bool hasParticle_ = false;
    bool subdivided_ = false;

    std::unique_ptr<QuadTree> children_[4];  // Children quadtrees 1: NE, 2: NW, 3: SW, 4: SE
    sf::Vector2f centerOfMass_ = {0.f, 0.f};  // Of the children
    float totalMass_ = 0.f;

    // Insert and mass update helpers
    void subdivide();
    bool isLeaf() const { return !subdivided_; }
    bool containsPoint(const sf::FloatRect& boundary, const sf::Vector2f& point) { return boundary.contains(point); }
    
};

#endif 