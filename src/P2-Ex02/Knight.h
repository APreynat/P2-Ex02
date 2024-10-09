#pragma once
#include "pch.h"

class Knight : public ChessPiece {
public:
    Knight(char color, std::string position);

    // Knight's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};