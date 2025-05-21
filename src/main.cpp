#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "BruteForce.h"
#include "BarnesHut.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation");
    

    ParticleSystem ps;
    ps.createRandomSystem(10000);
    ps.addParticle(1e18f, {500, 500});
    
    
    while (window.isOpen()) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }

        window.clear(sf::Color::Black);
        sf::Clock clock;
        auto forces = computeBarnesHutForces(ps.getParticles());
        float elapsed = clock.getElapsedTime().asMilliseconds(); 
        std::cout << elapsed << std::endl;
        ps.updateAndDraw(window, forces);

        window.display();
    }

    return 0;
}
