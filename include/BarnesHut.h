#ifndef BARNESHUT_H
#define BARNESHUT_H

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Particle.h"
#include "QuadTree.h"

std::vector<sf::Vector2f> computeBarnesHutForces(const std::vector<Particle>& particles);

#endif // BARNESHUT_H
