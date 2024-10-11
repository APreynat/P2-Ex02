#pragma once
#include "pch.h"

class Rook : public ChessPiece {
public:
    Rook(char color, char symbol, const sf::Texture& texture, std::string position);

    void setTexture(const sf::Texture& texture);

    // Rook's specific movement rules
    bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const override;
};