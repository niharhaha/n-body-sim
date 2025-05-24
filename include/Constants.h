#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

inline constexpr float G = 6.67e-11f;       // Gravitational constant
inline constexpr float TIME_STEP = 0.005f;      // Time step for simulation
inline constexpr float UNIT_RADIUS = 8.0f; // Default particle radius
inline constexpr int WINDOW_WIDTH = 1080.0f;
inline constexpr int WINDOW_HEIGHT = 720.0f;
inline constexpr float UNIT_MASS = 1e10f; // In kilograms
inline constexpr float THETA = 0.5f;  // Barnes-Hut theta threshold
inline constexpr float EPSILON = 1e-4f; 

inline constexpr float smallGap = 5.f;
inline constexpr float bigGap = 8.f;
inline constexpr float statTextSize = 24.f;
inline constexpr float resultTextSize = 44.f;
inline constexpr float headingTextSize = 70.f;

inline const sf::Vector2f WINDOW_TEXT_CORNER = {smallGap, smallGap};
inline const sf::Vector2f WINDOW_TEXT_CORNER2 = {smallGap, 2 * smallGap + statTextSize};

inline const sf::Vector2f WINDOW_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

inline const sf::Vector2f WINDOW_HEADING_TEXT_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - headingTextSize};
inline const sf::Vector2f WINDOW_RESULT_TEXT_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + bigGap};
inline const sf::Vector2f WINDOW_RESULT2_TEXT_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + resultTextSize + 2 * bigGap};
inline const sf::Vector2f WINDOW_RESULT3_TEXT_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 2 * resultTextSize + 3 * bigGap};
inline const sf::Vector2f WINDOW_RESULT4_TEXT_CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 3 * resultTextSize + 4 * bigGap};

inline const sf::Vector2f ZERO_VEC = {0.0f, 0.0f};
inline const sf::Color DEF_COLOR = sf::Color::Black;
const sf::FloatRect SCREEN({0.f, 0.f}, {WINDOW_WIDTH, WINDOW_HEIGHT});

#endif // CONSTANTS_H
