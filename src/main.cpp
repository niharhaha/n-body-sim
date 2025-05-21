#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "N-Body Gravity Simulation");

    while (window.isOpen()) {
        // pollEvent returns std::optional<sf::Event>
        std::optional<sf::Event> eventOpt = window.pollEvent();

        while (eventOpt.has_value()) {
            const sf::Event& event = eventOpt.value();

            // Check if event is of type Closed
            if (event.is<sf::Event::Closed>()) { window.close(); }
            eventOpt = window.pollEvent();
        }

        window.clear();
        window.display();
    }

    return 0;
}
