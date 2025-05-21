#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

inline constexpr float G = 6.67430e-11f;       // Gravitational constant
inline constexpr float TIME_STEP = 0.01f;      // Time step for simulation
inline constexpr float UNIT_RADIUS = 3.0f; // Default particle radius
inline constexpr float WINDOW_WIDTH = 1000.0f;
inline constexpr float WINDOW_HEIGHT = 1000.0f;
inline constexpr float UNIT_MASS = 1.0f;

inline const sf::Vector2f WINDOW_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
inline const sf::Vector2f ZERO_VELOCITY = {0.0f, 0.0f};
inline const sf::Color DEF_COLOR = sf::Color::Green;


#endif // CONSTANTS_H
