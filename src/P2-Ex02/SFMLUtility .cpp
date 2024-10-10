// SFMLUtility.cpp
#include "pch.h"
#include "SFMLUtility.h"

SFMLUtility::SFMLUtility() {}

SFMLUtility::~SFMLUtility() {}

// Load a font and return it
bool SFMLUtility::loadFont(sf::Font& font, const std::string& fontPath) {
    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font: " << fontPath << std::endl;
        return false;
    }
    return true;
}

// Create a text object
sf::Text SFMLUtility::createText(const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position) {
    sf::Text textObj;
    textObj.setFont(font);
    textObj.setCharacterSize(characterSize);
    textObj.setFillColor(color);
    textObj.setPosition(position);
    return textObj;
}

// Create a rectangle shape
sf::RectangleShape SFMLUtility::createRectangle(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness) {
    sf::RectangleShape rectangle(size);
    rectangle.setFillColor(fillColor);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOutlineThickness(outlineThickness);
    return rectangle;
}

// Draw a vector of shapes
template<typename ShapeType>
void SFMLUtility::drawShapes(sf::RenderWindow& window, const std::vector<ShapeType>& shapes) {
    for (const auto& shape : shapes) {
        window.draw(shape);
    }
}

// Handle mouse input
sf::Vector2i SFMLUtility::getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}
