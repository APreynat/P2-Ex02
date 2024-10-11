#include "pch.h"
#include "Bishop.h"

Bishop::Bishop(const std::string& image, const char symbol, std::pair<int, int> position, int player) : Piece(image, symbol, position, player) {

}


bool Bishop::isValidMove(std::pair<int, int> coordinate) const {
    int currentRow = position.second;
    int currentCol = position.first;

    int targetRow = coordinate.second;
    int targetCol = coordinate.first;

    // Bishop moves diagonally, which means the absolute difference between row and column must be the same
    return abs(currentRow - targetRow) == abs(currentCol - targetCol);
}