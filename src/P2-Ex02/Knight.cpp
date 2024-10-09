#include "pch.h"
#include "Knight.h"

Knight::Knight(char color, std::string position) : ChessPiece(color, 'N', position) {}

bool Knight::isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const {
    int currentRow = position[1] - '1';
    int currentCol = position[0] - 'A';
    int newRow = newPosition[1] - '1';
    int newCol = newPosition[0] - 'A';

    int rowDiff = abs(newRow - currentRow);
    int colDiff = abs(newCol - currentCol);

    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);  // Knight moves in L-shape
}
