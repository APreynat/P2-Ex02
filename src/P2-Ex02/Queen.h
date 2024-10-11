#pragma once
#include "pch.h"

class Queen : public Piece
{
public:
	Queen(const std::string& image, const char symbol, std::pair<int, int> position, int player);

	bool isValidMove(std::pair<int, int> coordinate) const override;


private:

};