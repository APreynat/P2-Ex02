#include "pch.h"
#include "Board.h"
#include "ChessPiece.h"

Board::Board() {
    // Initialize the grid with nullptr
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            grid[i][j] = nullptr;
        }
    }
}

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete grid[i][j];
        }
    }
}

void Board::placePiece(ChessPiece* piece, std::string position) {
    int row, col;
    if (getPositionIndices(position, row, col)) {
        if (grid[row][col] != nullptr) {
            delete grid[row][col];
        }
        grid[row][col] = piece;
        piece->move(position);
    }
}

bool Board::isPathClear(int fromRow, int fromCol, int toRow, int toCol) const {
    // Path checking logic remains the same (can be refined for diagonal checks)
    return true;
}

bool Board::movePiece(std::string fromPosition, std::string toPosition) {
    int fromRow, fromCol, toRow, toCol;
    if (getPositionIndices(fromPosition, fromRow, fromCol) &&
        getPositionIndices(toPosition, toRow, toCol)) {
        ChessPiece* piece = grid[fromRow][fromCol];
        if (piece && piece->isValidMove(toPosition, grid)) {
            delete grid[toRow][toCol];  // Remove the piece at the destination
            grid[toRow][toCol] = piece;
            grid[fromRow][fromCol] = nullptr;
            piece->move(toPosition);
            return true;
        }
    }
    return false;
}

void Board::display(sf::RenderWindow& window) const {
    // Debug: Check texture size to verify it loaded properly
    sf::Vector2u textureSize = boardTexture.getSize();
    if (textureSize.x == 0 || textureSize.y == 0) {
        MessageBoxA(nullptr, "Chessboard texture is not loaded properly!", "Error", MB_OK | MB_ICONERROR);
        return ;
    }

    // Draw the board
    window.draw(boardSprite);

    // Draw each piece on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (grid[row][col]) {
                float x = col * 81;  // Assume each square is 81x81 pixels
                float y = row * 81;
                grid[row][col]->setSpritePosition(x, y);
                grid[row][col]->draw(window);
            }
        }
    }
}

bool Board::getPositionIndices(std::string position, int& row, int& col) const {
    if (position.length() == 2) {
        col = position[0] - 'A';
        row = 8 - (position[1] - '1') - 1;
        return (col >= 0 && col < 8 && row >= 0 && row < 8);
    }
    return false;
}

// Load the chessboard texture and any required resources
bool Board::loadSprite() {
    // This method should load the texture and return whether it was successful
    if (!boardTexture.loadFromFile("../../../Images/chessboard.png")) {
        return false;  // Return false if loading failed
    }
    boardSprite.setTexture(boardTexture);  // Set the texture to the sprite
    return true;  // Return true if loading was successful
}

// Getter for board texture
sf::Texture Board::GetTexture() const {
    return boardTexture;
}

// Getter for board sprite
sf::Sprite Board::GetSprite() const {
    return boardSprite;
}