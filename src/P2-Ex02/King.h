#pragma once
#include "pch.h"

class King : public ChessPiece {
public:
    King(char color, std::string position);

    // King's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};