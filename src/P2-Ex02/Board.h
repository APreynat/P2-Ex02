#pragma once
#include "pch.h"

class ChessPiece; // Forward declaration of ChessPiece

class Board {
private:
    ChessPiece* grid[8][8];  // Holds chess pieces
    sf::Texture boardTexture; // Texture for the chessboard
    sf::Sprite boardSprite;   // Sprite for displaying the chessboard

public:
    Board();
    ~Board();
    void placePiece(ChessPiece* piece, std::string position);
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) const;
    bool movePiece(std::string fromPosition, std::string toPosition);
    void display(sf::RenderWindow& window) const; // Render method for displaying the board and pieces
    bool getPositionIndices(std::string position, int& row, int& col) const;

    // Load the chessboard texture and any required resources
    bool loadTextures(const std::string& boardImagePath);
};
