#include "pch.h"
#include "King.h"

King::King(char color, std::string position) : ChessPiece(color, 'K', position) {}

bool King::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';

    return (abs(newRow - currentRow) <= 1 && abs(newCol - currentCol) <= 1);  // King moves one square
}
