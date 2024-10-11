#include "pch.h"
#include "Bishop.h"

Bishop::Bishop(char color, char symbol, const sf::Texture& texture, std::string position) : ChessPiece(color, 'B', texture, position) {}

// Set the texture for the Bishop piece using the TextureManager
void Bishop::setTexture(const sf::Texture& texture) {
    loadSprite(texture); // Call the loadSprite method from ChessPiece
}

bool Bishop::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';
    int rowDiff = abs(newRow - currentRow);
    int colDiff = abs(newCol - currentCol);

    return (rowDiff == colDiff);  // Diagonal move
}
