#include "pch.h"
#include "King.h"

King::King(const std::string& image, const char symbol, std::pair<int, int> position, int player) : Piece(image, symbol, position, player) {

}


bool King::isValidMove(std::pair<int, int> coordinate) const {
    int currentRow = position.second;
    int currentCol = position.first;

    int targetRow = coordinate.second;
    int targetCol = coordinate.first;

    // King moves exactly one square in any direction
    return abs(currentRow - targetRow) <= 1 && abs(currentCol - targetCol) <= 1;
}
