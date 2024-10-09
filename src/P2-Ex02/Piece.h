#ifndef PIECE_H
#define PIECE_H
#include "pch.h"
#include <utility> // For std::pair
#include <string>

class Piece {
public:
    Piece(const std::string& symbol, std::pair<int, int> position, int player);
    virtual ~Piece() = default;

    std::string GetImage() const;
    std::pair<int, int> getPosition() const; // Return pair of ints for (col, row)
    void setPosition(std::pair<int, int> newPosition); // Take a pair for (col, row)
    int getPlayer() const;
    void setPlayer(int player);

    virtual bool isValidMove(std::pair<int, int> coordinate) const = 0;

protected:
    std::string symbol;
    std::pair<int, int> position; // Store position as a (col, row) pair
    std::string color;
    int player;
};

#endif