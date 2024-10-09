#ifndef PAWN_H
#define PAWN_H
#include "pch.h"

class Pawn : public Piece {
public:

    Pawn(const std::string& image, const  std::pair<int, int> position, int player);


    bool isValidMove(std::pair<int, int> coordinate) const override;

protected :
    
};

#endif // PAWN_H