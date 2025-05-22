#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

inline constexpr float G = 6.67e-11f;       // Gravitational constant
inline constexpr float TIME_STEP = 0.005f;      // Time step for simulation
inline constexpr float UNIT_RADIUS = 8.0f; // Default particle radius
inline constexpr int WINDOW_WIDTH = 700.0f;
inline constexpr int WINDOW_HEIGHT = 700.0f;
inline constexpr float UNIT_MASS = 1e10f; // In kilograms
inline constexpr float THETA = 0.5f;  // Barnes-Hut theta threshold
inline constexpr float EPSILON = 1e-6f; 
const float AU = 1.496e11f;   // Astronomical Unit in meters (distance Earth-Sun)
const float SCALE = 1e-9f;    
const sf::FloatRect SCREEN({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT});
inline const sf::Vector2f WINDOW_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
inline const sf::Vector2f ZERO_VEC = {0.0f, 0.0f};
inline const sf::Color DEF_COLOR = sf::Color::Black;

#endif // CONSTANTS_H
