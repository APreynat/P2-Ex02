// SFMLUtility.h

#pragma once

class SFMLUtility {
public:
    SFMLUtility();
    ~SFMLUtility();

    // Load a font and return it
    bool loadFont(sf::Font& font, const std::string& fontPath);

    // Create a text object
    sf::Text createText(const sf::Font& font, unsigned int characterSize, const sf::Color& color, const sf::Vector2f& position);

    // Create a rectangle shape
    sf::RectangleShape createRectangle(const sf::Vector2f& size, const sf::Color& fillColor, const sf::Color& outlineColor, float outlineThickness);

    // Draw a vector of shapes
    template<typename ShapeType>
    void drawShapes(sf::RenderWindow& window, const std::vector<ShapeType>& shapes);

    // Handle mouse input
    sf::Vector2i getMousePosition(sf::RenderWindow& window);
};

