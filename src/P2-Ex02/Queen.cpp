#include "pch.h"
#include "Queen.h"


Queen::Queen(const std::string& image, std::pair<int, int> position, int player) : Piece(image, position, player) {

}

bool Queen::isValidMove(std::pair<int, int> coordinate) const {
    int currentRow = position.second;
    int currentCol = position.first;

    int targetRow = coordinate.second;
    int targetCol = coordinate.first;

    // Queen moves like both a rook (straight lines) and a bishop (diagonals)
    return (currentRow == targetRow || currentCol == targetCol) ||
        (abs(currentRow - targetRow) == abs(currentCol - targetCol));
}
