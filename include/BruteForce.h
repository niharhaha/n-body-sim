#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <vector>
#include "Particle.h"

// The O(n^2) algorithm 
std::vector<sf::Vector2f> computeBruteForces(const std::vector<Particle>& particles);

#endif 
