#include "pch.h"
#include "Queen.h"

// Constructor
Queen::Queen(char color, char symbol, const sf::Texture& texture, std::string position) : ChessPiece(color, 'Q', texture, position) {}

void Queen::setTexture(const sf::Texture& texture) {
    loadSprite(texture); // Call the loadSprite method from ChessPiece
}

// Queen's movement combines both rook and bishop logic
bool Queen::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';

    int rowDiff = abs(newRow - currentRow);
    int colDiff = abs(newCol - currentCol);

    // Straight-line movement (like a rook) or diagonal movement (like a bishop)
    if (rowDiff == 0 || colDiff == 0 || rowDiff == colDiff) {
        return true;  // Valid rook-like or bishop-like move
    }

    return false;
}
