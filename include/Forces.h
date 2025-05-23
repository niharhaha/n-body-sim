#ifndef FORCES_H
#define FORCES_H

#include <vector>
#include "Particle.h"
#include <SFML/System/Vector2.hpp>
#include "QuadTree.h"
#include "ParticleSystem.h"
// The O(n^2) algorithm 
void computeBruteForces(ParticleSystem& ps);

// Barnes Hut O(nlogn) (approximation) algorithm
void computeBarnesHutForces(ParticleSystem& ps);

// Barnes Hut O(nlogn) (approximation) algorithm w/ Threading
void computeThreadPoolBarnesHutForces(ParticleSystem& ps, ThreadPool& pool);

#endif 
