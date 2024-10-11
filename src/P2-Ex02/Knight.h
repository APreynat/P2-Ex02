#pragma once
#include "pch.h"

class Knight : public ChessPiece {
public:
    Knight(char color, char symbol, const sf::Texture& texture, std::string position);

    void setTexture(const sf::Texture& texture);

    // Knight's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};