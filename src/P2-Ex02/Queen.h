#pragma once
#include "pch.h"

class Queen : public ChessPiece {
public:
    Queen(char color, std::string position);

    // Queen's specific movement rules (combines Rook and Bishop movement)
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};