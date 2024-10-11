#include "pch.h"
#include "Pawn.h"


Pawn::Pawn(const std::string& image, std::pair<int, int> position, int player) : Piece(image, position, player) {

}


bool Pawn::isValidMove(std::pair<int, int> coordinate) const {
    int currentRow = position.second; // row (y)
    int currentCol = position.first;  // col (x)

    int targetRow = coordinate.second; // target row (y)
    int targetCol = coordinate.first;  // target col (x)

    int direction = (getPlayer() == 1) ? 1 : -1;

    // Moving forward by 1
    if (targetCol == currentCol && targetRow == currentRow + direction) {
        return true; // Valid move forward
    }

    // Initial double move
    if (currentRow == (getPlayer() == 1 ? 1 : 6) && targetCol == currentCol && targetRow == currentRow + 2 * direction) {
        return true; // Valid double move from starting position
    }

    // Capturing diagonally
    if (abs(targetCol - currentCol) == 1 && targetRow == currentRow + direction) {
        return true; // Valid capture
    }

    // If none of the conditions match
    std::cout << "Invalid move for player " << getPlayer() << " from " << currentRow << "," << currentCol << " to " << targetRow << "," << targetCol << std::endl;
    return false; // Not a valid move
}


