#pragma once
#include "pch.h"

class Rook : public ChessPiece {
public:
    Rook(char color, std::string position);

    // Rook's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};