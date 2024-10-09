#include "pch.h"
#include "Knight.h"

Knight::Knight(const std::string& image, std::pair<int, int> position, int player) : Piece(image, position, player) {}


bool Knight::isValidMove(std::pair<int, int> coordinate) const {

    int currentRow = position.second;
    int currentCol = position.first;

    int targetRow = coordinate.second;
    int targetCol = coordinate.first;

    // Knight moves in an "L" shape: 2 squares in one direction, 1 square in the perpendicular direction
    return (abs(currentRow - targetRow) == 2 && abs(currentCol - targetCol) == 1) ||
        (abs(currentRow - targetRow) == 1 && abs(currentCol - targetCol) == 2);
}