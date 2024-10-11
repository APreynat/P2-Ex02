#pragma once
#include "pch.h"

class Bishop : public Piece
{
public:
	Bishop(const std::string& image, const char symbol, std::pair<int, int> position, int player);

	bool isValidMove(std::pair<int, int> coordinate) const override;


private:

};