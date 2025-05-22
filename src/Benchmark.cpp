#include "ParticleSystem.h"
#include "Forces.h"
#include <iostream>
#include <SFML/Graphics.hpp>   // For sf::RenderWindow, sf::Text, sf::Font, sf::Color
#include "ThreadPool.h"
#include "Simulation.h"

void benchmarkThreadedBarnesHut(int size = 10000, int iters = 2500) {
    ParticleSystem ps;
    ps.createRandomSystem(size);   
    // ps.addParticle(1e18f, {500, 500}, {-5, -15}, 15, {180, 14, 77});
    ps.addParticle(1e18f, {200, 500}, {-5, -15}, 15, {180, 14, 77});
    ThreadPool pool;

    createIterSimulation(ps, [&pool](ParticleSystem& ps_ref) { computeThreadPoolBarnesHutForces(ps_ref, pool); }, iters);
}

void benchmarkBarnesHut(int size = 100000, int iters = 5000) {
    ParticleSystem ps;
    ps.createRandomSystem(size);   
    // ps.addParticle(1e18f, {500, 500}, {-5, -15}, 15, {180, 14, 77});
    ps.addParticle(1e18f, {200, 500}, {-5, -15}, 15, {180, 14, 77});

    createTimeSimulation(ps, [](ParticleSystem& ps_ref) { computeBarnesHutForces(ps_ref); }, iters);
}