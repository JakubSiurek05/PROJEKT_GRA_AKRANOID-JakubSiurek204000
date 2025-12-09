#include "Stone.h"
#include <array>

const std::array<sf::Color, 4> Stone::m_colorLUT = {
    sf::Color::Transparent, // L = 0
    sf::Color::Red,         // L = 1
    sf::Color::Yellow,      // L = 2
    sf::Color::Blue         // L = 3
};