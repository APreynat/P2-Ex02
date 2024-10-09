#include "pch.h"

class King : public Piece
{
public:
	King(const std::string& image, std::pair<int, int> position, int player);

	bool isValidMove(std::pair<int, int> coordinate) const override;


private:

};