#pragma once
#include "pch.h"

class Pawn : public Piece {
public:

    Pawn(const std::string& image, const char symbol, std::pair<int, int> position, int player);


    bool isValidMove(std::pair<int, int> coordinate) const override;

protected :
    
};