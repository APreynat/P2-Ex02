#include "pch.h"
#include "TextureManager.h"

// Constructor
ChessPiece::ChessPiece(char color, char symbol, const sf::Texture& texture, std::string position): color(color), symbol(symbol), position(position), hasMoved(false) {
    pieceSprite.setTexture(texture);  // Set the shared texture to the sprite
}

// Getter implementations remain unchanged
char ChessPiece::getSymbol() const { return symbol; }
char ChessPiece::getColor() const { return color; }
std::string ChessPiece::getPosition() const { return position; }
bool ChessPiece::getHasMoved() const { return hasMoved; }

// Move method
void ChessPiece::move(std::string newPosition) {
    position = newPosition;
    hasMoved = true;
}

// Loading texture from file
bool ChessPiece::loadTexture(const std::string& texturePath) {
    if (!pieceTexture.loadFromFile(texturePath)) {
        MessageBox(nullptr, L"Failed to load piece texture!", L"Error", MB_OK | MB_ICONERROR);  // Debug message
        return false;
    }
    pieceSprite.setTexture(pieceTexture);
    return true;
}

void ChessPiece::loadSprite(const sf::Texture& texture) {
    pieceSprite.setTexture(texture);
}

// Setting the sprite position for the SFML window
void ChessPiece::setSpritePosition(float x, float y) {
    pieceSprite.setPosition(x, y);
}

// Draw method for rendering the piece
void ChessPiece::draw(sf::RenderWindow& window) const {
    window.draw(pieceSprite);
}
