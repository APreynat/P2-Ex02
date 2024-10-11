#pragma once

#include "Piece.h"  // Include the Piece header to inherit from it
#include <string>
#include <utility>

class Rook : public Piece
{
public:
    Rook(const std::string& image, const char symbol, std::pair<int, int> position, int player);
    virtual bool isValidMove(std::pair<int, int> coordinate) const override;

private:

};
