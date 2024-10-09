#pragma once
#include "pch.h"

class Pawn : public ChessPiece {
public:
    Pawn(char color, std::string position);

    // Pawn's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};