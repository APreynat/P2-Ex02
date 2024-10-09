#include "pch.h"
#include "Rook.h"

// Constructor
Rook::Rook(char color, std::string position) : ChessPiece(color, 'R', position) {}

// Rook's specific movement rules
bool Rook::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';

    // Rook moves in straight lines (either same row or same column)
    return (currentRow == newRow || currentCol == newCol);
}
