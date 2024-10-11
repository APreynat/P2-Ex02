#include "pch.h"
#include "Pawn.h"

// Constructor
Pawn::Pawn(char color, char symbol, const sf::Texture& texture, std::string position) : ChessPiece(color, 'P', texture, position) {}

void Pawn::setTexture(const sf::Texture& texture) {
    loadSprite(texture); // Call the loadSprite method from ChessPiece
}

// Pawn's specific movement rules
bool Pawn::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';

    int rowDiff = newRow - currentRow;

    // Moving forward one square
    if (currentCol == newCol && rowDiff == 1 && !grid[newRow][newCol]) {
        return true;
    }

    // Moving two squares forward from initial position
    if (currentCol == newCol && rowDiff == 2 && currentRow == 1 && !grid[newRow][newCol] && !grid[newRow - 1][newCol]) {
        return true;
    }

    // Capturing diagonally
    if (abs(newCol - currentCol) == 1 && rowDiff == 1 && grid[newRow][newCol] && grid[newRow][newCol]->getColor() != this->getColor()) {
        return true;
    }

    return false;
}
