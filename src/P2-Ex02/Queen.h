#pragma once
#include "pch.h"

class Queen : public ChessPiece {
public:
    Queen(char color, char symbol, const sf::Texture& texture, std::string position);

    void setTexture(const sf::Texture& texture);

    // Queen's specific movement rules (combines Rook and Bishop movement)
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};