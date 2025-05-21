#include <SFML/Graphics.hpp>
#include <optional>
#include "Particle.h"
#include "Constants.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "N-Body Gravity Simulation");
    sf::Clock clock;

    while (window.isOpen()) {
        std::optional<sf::Event> eventOpt = window.pollEvent();
        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();
            if (event.is<sf::Event::Closed>()) window.close();
            eventOpt = window.pollEvent();
        }

        float dt = clock.restart().asSeconds();
    }

    return 0;
}
