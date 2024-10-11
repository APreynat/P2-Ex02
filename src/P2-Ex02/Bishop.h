#pragma once
#include "pch.h"

class Bishop : public ChessPiece {
public:
    Bishop(char color, char symbol, const sf::Texture& texture, std::string position);

    void setTexture(const sf::Texture& texture);

    // Bishop's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};