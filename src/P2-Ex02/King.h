#pragma once
#include "pch.h"

class King : public ChessPiece {
public:
    King(char color, char symbol, const sf::Texture& texture, std::string position);

    void setTexture(const sf::Texture& texture);

    // King's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};