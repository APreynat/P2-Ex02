#include "pch.h"
#include "Piece.h"

Piece::Piece(const std::string& symbol, std::pair<int, int> position, int player)
    : symbol(symbol), position(position), player(player) {
}

std::string Piece::GetImage() const {
    return symbol;
}

std::pair<int, int> Piece::getPosition() const {
    return position;
}

void Piece::setPosition(std::pair<int, int> newPosition) {
    position = newPosition;
}

int Piece::getPlayer() const {
    return player;
}

void Piece::setPlayer(int player) {
    this->player = player;
}