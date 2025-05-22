#ifndef FORCES_H
#define FORCES_H

#include <vector>
#include "Particle.h"
#include <SFML/System/Vector2.hpp>
#include "QuadTree.h"

// The O(n^2) algorithm 
std::vector<sf::Vector2f> computeBruteForces(const std::vector<Particle>& particles);

// Barnes Hut O(nlogn) (approximation) algorithm
std::vector<sf::Vector2f> computeBarnesHutForces(const std::vector<Particle>& particles);

// Barnes Hut O(nlogn) (approximation) algorithm w/ Threading
std::vector<sf::Vector2f> computeThreadedBarnesHutForces(const std::vector<Particle>& particles);

#endif 
