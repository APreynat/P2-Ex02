#include "pch.h"

class Knight : public Piece
{
public:
	Knight(const std::string& image, std::pair<int, int> position, int player);
	virtual bool isValidMove(std::pair<int, int> coordinate) const override;


private:

};