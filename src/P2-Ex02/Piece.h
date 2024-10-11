#pragma once
#include "pch.h"
#include <utility> // For std::pair
#include <string>

class Piece {
public:
    Piece(const std::string& image, const char symbol, std::pair<int, int> position, int player);
    virtual ~Piece() = default;

    std::string GetImage() const;
    char getSymbol() const;
    std::pair<int, int> getPosition() const;
    int getPlayer() const;
    

    void setPosition(std::pair<int, int> newPosition);
    void setPlayer(int player);

    virtual bool isValidMove(std::pair<int, int> coordinate) const = 0;

protected:
    std::string image;
    char symbol;
    std::pair<int, int> position; // Store position as a (col, row) pair
    std::string color;
    int player;
};