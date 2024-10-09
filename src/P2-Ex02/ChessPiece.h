#pragma once
#include "pch.h"

class ChessPiece {
protected:
    char color;     // 'W' for white, 'B' for black
    char symbol;    // Piece symbol, e.g., 'P' for pawn, 'R' for rook
    std::string position; // Current position as a string, e.g., "A2"
    bool hasMoved;  // Track if the piece has moved

    sf::Texture pieceTexture;  // Texture for the piece
    sf::Sprite pieceSprite;    // Sprite for rendering the piece

public:
    ChessPiece(char color, char symbol, std::string position);

    // Getters
    char getColor() const;
    char getSymbol() const;
    std::string getPosition() const;
    bool getHasMoved() const;

    // Set the piece texture (from an image file)
    bool loadTexture(const std::string& texturePath);

    // Method to set the position of the sprite on the board
    void setSpritePosition(float x, float y);

    // Virtual method to check if a move is valid
    virtual bool isValidMove(std::string newPosition, ChessPiece* grid[8][8]) const = 0;

    // Move the piece to a new position
    void move(std::string newPosition);

    // Draw the piece on the board
    void draw(sf::RenderWindow& window) const;

    virtual ~ChessPiece() {}
};