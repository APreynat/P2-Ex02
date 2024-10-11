#include "pch.h"
#include "Rook.h"


Rook::Rook(const std::string& image, const char symbol, std::pair<int, int> position, int player) : Piece(image, symbol, position, player) {

}


#include "Rook.h"
#include "Board.h"

bool Rook::isValidMove(std::pair<int, int> coordinate) const {
    int currentRow = position.second;
    int currentCol = position.first;

    int targetRow = coordinate.second;
    int targetCol = coordinate.first;

    // Rook moves in straight lines
    if (currentRow == targetRow || currentCol == targetCol) {
        // Check if the path is clear
        return true; // Assume path is clear. You may want to implement a check to see if it is occupied.
    }

    return false;
}

