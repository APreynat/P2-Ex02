#pragma once
#include "pch.h"

class ChessPiece; // Forward declaration of ChessPiece

class Board {
private:
      // Holds chess pieces
    sf::Texture boardTexture; // Texture for the chessboard
    sf::Sprite boardSprite;   // Sprite for displaying the chessboard

public:
    Board();
    ~Board();
    ChessPiece* grid[8][8];
    void placePiece(ChessPiece* piece, string position);
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) const;
    bool movePiece(std::string fromPosition, string toPosition);
    void display(sf::RenderWindow& window) const; // Render method for displaying the board and pieces
    bool getPositionIndices(string position, int& row, int& col) const;

    // Load the chessboard texture and any required resources
    bool loadSprite();

    sf::Texture GetTexture() const;  // Get the board texture
    sf::Sprite GetSprite() const;    // Get the board sprite
};
