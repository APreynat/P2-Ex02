#include "pch.h"
#include "SFMLUtility.h"

SFMLUtility::SFMLUtility() {}

SFMLUtility::~SFMLUtility() {}

// Handle mouse input
sf::Vector2i SFMLUtility::getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}