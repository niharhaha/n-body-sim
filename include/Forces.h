#ifndef FORCES_H
#define FORCES_H

#include <vector>
#include "Particle.h"
#include <SFML/System/Vector2.hpp>
#include "QuadTree.h"

// The O(n^2) algorithm 
void computeBruteForces(const std::vector<Particle>& particles, std::vector<sf::Vector2f>& forces);

// Barnes Hut O(nlogn) (approximation) algorithm
void computeBarnesHutForces(const std::vector<Particle>& particles, std::vector<sf::Vector2f>& forces);

// Barnes Hut O(nlogn) (approximation) algorithm w/ Threading
void computeThreadPoolBarnesHutForces(const std::vector<Particle>& particles, std::vector<sf::Vector2f>& forces, ThreadPool& pool);

#endif 
