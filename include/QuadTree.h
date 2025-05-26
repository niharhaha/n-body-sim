#ifndef QUAD_TREE_H
#define QUAD_TREE_H

#include "Particle.h"
#include <memory>

class QuadTree {
public:
    // Constructors
    QuadTree(){ tree_.emplace_back(Quad()); };
    QuadTree(const std::vector<Particle>& particles);

    bool insertParticle(const Particle& p); // Add particle to QuadTree
    sf::Vector2f computeForceOnTarget(const Particle& target); // Use QuadTree to compute mass on particle
    
private:
    struct Quad {
        sf::Vector2f origin = WINDOW_CENTER;
        float height = WINDOW_HEIGHT;
        float width = WINDOW_WIDTH;

        Quad(sf::Vector2f o = WINDOW_CENTER, 
             float w = WINDOW_WIDTH, 
             float h = WINDOW_HEIGHT)
            : origin(o), width(w), height(h) {}

    };

    struct QuadTreeNode {
        Quad region;

        int child_idx = -1; // Index in tree_ of NE child; other 3 are contiguous
        sf::Vector2f centerOfMass = {0.f, 0.f};
        float totalMass = 0.f;   
        bool subdivided = false;
        bool hasParticle = false;
        const Particle* particle = nullptr;    

        QuadTreeNode() = default;
        QuadTreeNode(const Quad& q) : region(q) {}

        bool containsPoint(const sf::Vector2f pos) {
            return (region.origin.x - region.width / 2 <= pos.x && pos.x < region.origin.x + region.width / 2) && (region.origin.y - region.height / 2 <= pos.y && pos.y < region.origin.y + region.height / 2);
        }

        bool containsPoint(const Particle& p) {
            return containsPoint(p.getPosition());
        }

        bool isLeaf() const { return !subdivided; }
    };
    
    std::vector<QuadTreeNode> tree_;

    // Insert and mass update helpers
    void updateMassDistribution(); // Propogate QuadTree mass
    void subdivide(int idx);
    bool insertParticle(int idx, const Particle& p); // Add particle to QuadTree
    void updateMassDistribution(int idx); // Propogate QuadTree mass
    sf::Vector2f computeForceOnTarget(int idx, const Particle& target); // Use QuadTree to compute mass on particle
};

#endif 