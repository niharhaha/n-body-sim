#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "ParticleSystem.h"
#include "Constants.h"
#include "BruteForce.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "N-Body Gravity Simulation");
    sf::Clock clock;

    ParticleSystem ps;
    ps.createRandomSystem(100);
    
    while (window.isOpen()) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }

        window.clear(sf::Color::Black);
        auto forces = computeBruteForces(ps.getParticles());
        ps.updateAndDraw(window, forces);

        window.display();


    }

    return 0;
}
