#include "pch.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<Piece*>(cols, nullptr));
}


void Board::display(sf::RenderWindow& window) const {
    if (!boardTexture.loadFromFile("../../../img/ChessBoard.png")) {
        std::cerr << "Error loading board texture" << std::endl;
        return;
    }
    sf::Sprite boardSprite(boardTexture);
    const int squareSize = 64;

    window.draw(boardSprite);

    // Draw each piece
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Piece* piece = grid[i][j];
            if (piece != nullptr) {
                sf::Texture pieceTexture;
                if (pieceTexture.loadFromFile(piece->GetImage())) {
                    sf::Sprite pieceSprite(pieceTexture);
                    pieceSprite.setPosition(j * squareSize, i * squareSize);
                    window.draw(pieceSprite);
                }
            }
        }
    }
}

void Board::initializeGame() {
    // Clear the board and resize it to 8x8
    grid.clear();
    grid.resize(8, std::vector<Piece*>(8, nullptr));

    // Set up player 1 (white pieces)
    grid[0][0] = new Rook("../../../img/Chess_rlt60.png", { 0, 0 }, 1);  // A1
    grid[0][1] = new Knight("../../../img/Chess_nlt60.png", { 1, 0 }, 1);  // B1
    grid[0][2] = new Bishop("../../../img/WhiteBishop.png", { 2, 0 }, 1);  // C1
    grid[0][3] = new Queen("../../../img/Chess_qlt60.png", { 3, 0 }, 1);  // D1
    grid[0][4] = new King("../../../img/Chess_klt60.png", { 4, 0 }, 1);  // E1
    grid[0][5] = new Bishop("../../../img/WhiteBishop.png", { 5, 0 }, 1);  // F1
    grid[0][6] = new Knight("../../../img/Chess_nlt60.png", { 6, 0 }, 1);  // G1
    grid[0][7] = new Rook("../../../img/Chess_rlt60.png", { 7, 0 }, 1);  // H1

    // White pawns
    for (int col = 0; col < 8; ++col) {
        grid[1][col] = new Pawn("../../../img/Chess_plt60.png", { col, 1 }, 1);  // Pawns in row 2
    }

    // Set up player 2 (black pieces)
    grid[7][0] = new Rook("../../../img/Chess_rdt60.png", { 0, 7 }, 2);  // A8
    grid[7][1] = new Knight("../../../img/Chess_ndt60.png", { 1, 7 }, 2);  // B8
    grid[7][2] = new Bishop("../../../img/BlackBishop.png", { 2, 7 }, 2);  // C8
    grid[7][3] = new Queen("../../../img/Chess_qdt60.png", { 3, 7 }, 2);  // D8
    grid[7][4] = new King("../../../img/Chess_kdt60.png", { 4, 7 }, 2);  // E8
    grid[7][5] = new Bishop("../../../img/BlackBishop.png", { 5, 7 }, 2);  // F8
    grid[7][6] = new Knight("../../../img/Chess_ndt60.png", { 6, 7 }, 2);  // G8
    grid[7][7] = new Rook("../../../img/Chess_rdt60.png", { 7, 7 }, 2);  // H8

    // Black pawns
    for (int col = 0; col < 8; ++col) {
        grid[6][col] = new Pawn("../../../img/Chess_pdt60.png", { col, 6 }, 2);  // Pawns in row 7
    }

    // Randomly select the first player
    srand(static_cast<unsigned int>(time(0)));  // Seed for random number generation
    currentPlayer = (rand() % 2) + 1;  // Randomly set to 1 or 2
}

Piece* Board::GetPiece(int col, int row) {
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        return grid[row][col]; // Notice it's [row][col] because grid is row-major
    }
    return nullptr;
}

int Board::GetCurrentPlayer() const {
    return currentPlayer;
}

bool Board::isOccupied(int row, int col) const {

    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return true;
    }

    return grid[row][col] != nullptr;
}

int Board::GetHintNumber() { return hintNumber; }

void Board::setHintNumber(int value) { hintNumber = value; }

bool Board::CanPlay(Piece& piece, const std::pair<int, int> coord) {
    std::pair<int, int> targetCoordinate = coord;
    std::pair<int, int> currentCoordinate = piece.getPosition();
    int currentRow = currentCoordinate.first;
    int currentCol = currentCoordinate.second;
    int targetRow = targetCoordinate.first;
    int targetCol = targetCoordinate.second;

    if (!piece.isValidMove(targetCoordinate)) {
        return false;
    }
    if (dynamic_cast<const Pawn*>(&piece)) {
        int currentRow = piece.getPosition().first;
        int currentCol = piece.getPosition().second;

        // Moving forward: must not be blocked
        if (targetCol == currentCol && grid[targetRow][targetCol] != nullptr) {
            return false; // Piece is directly in front
        }

        // Diagonal capture: must have an opponent's piece
        if (abs(targetCol - currentCol) == 1 && grid[targetRow][targetCol] == nullptr) {
            return false; // No piece to capture
        }
    }

    
    


    int rowStep = (targetRow - currentRow) == 0 ? 0 : (targetRow - currentRow) > 0 ? 1 : -1;
    int colStep = (targetCol - currentCol) == 0 ? 0 : (targetCol - currentCol) > 0 ? 1 : -1;

    // Check the path for any obstructing pieces
    int r = currentRow + rowStep;
    int c = currentCol + colStep;

    while (r != targetRow || c != targetCol) {
        if (isOccupied(r, c)) {  // Check if the square is occupied
            return false; // There is a piece in the way
        }
        r += rowStep;
        c += colStep;
    }

    Piece* targetPiece = GetPiece(targetRow, targetCol);
    if (targetPiece != nullptr && targetPiece->getPlayer() == piece.getPlayer()) {
        return false; // Invalid move, can't capture own piece
    }

    return true; // Move is valid
}

void Board::MovePiece(Piece& piece, std::pair<int, int> coord) {
    std::pair<int, int> targetCoordinate = coord;

    if (CanPlay(piece, coord)) {
        std::pair<int, int> currentCoordinate = piece.getPosition();
        int currentRow = currentCoordinate.first;
        int currentCol = currentCoordinate.second;

        // Update the grid
        grid[targetCoordinate.first][targetCoordinate.second] = &piece; // Place piece in new position
        grid[currentRow][currentCol] = nullptr; // Clear old position

        // Update the piece's position
        piece.setPosition(coord);

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch player
    }
    else {
        std::cout << "Invalid move" << std::endl;
    }
}




