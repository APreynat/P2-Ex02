#pragma once
#include "pch.h"

class Bishop : public ChessPiece {
public:
    Bishop(char color, std::string position);

    // Bishop's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};