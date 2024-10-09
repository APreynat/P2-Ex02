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

    // Load board texture (chessboard image)
    boardTexture.loadFromFile("path_to_board_texture.png");
    boardSprite.setTexture(boardTexture);
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
    window.draw(boardSprite);  // Draw the board

    // Draw each piece on the board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (grid[row][col]) {
                float x = col * 100;  // Assume each square is 100x100 pixels
                float y = row * 100;
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

bool Board::loadTextures(const std::string& boardImagePath) {
    return boardTexture.loadFromFile(boardImagePath);  // Load board texture
}
