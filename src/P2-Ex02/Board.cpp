#include "pch.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#ifdef SFML
Board::Board(int rows, int cols, sf::RenderWindow& window) : rows(rows), cols(cols), window(&window) {
    grid.resize(rows, std::vector<Piece*>(cols, nullptr));
}
#elif defined CONSOLE
Board::Board(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<Piece*>(cols, nullptr));
}
#endif // SFML




void Board::display() const {
#ifdef SFML
    if (!boardTexture.loadFromFile("../../../img/ChessBoard.png")) {
        std::cerr << "Error loading board texture" << std::endl;
        return;
}
    sf::Sprite boardSprite(boardTexture);
    const int squareSize = 64;

    window->draw(boardSprite);
#elif defined (CONSOLE)
    std::cout << "  Y ";
    for (char col = '0'; col < '0' + cols; ++col) {
        std::cout << col << ' ';
    }
    std::cout << std::endl << "X  ____" << "\033[31m" << "Player 1" << "\033[0m" << "____";

#endif // SFML

    

    // Draw each piece
    for (int i = 0; i < rows; ++i) {
        std::cout << std::endl << std::to_string(i) << " | ";
        for (int j = 0; j < cols; ++j) {
            Piece* piece = grid[i][j];
            if (piece != nullptr) {
#ifdef SFML
                sf::Texture pieceTexture;
                if (pieceTexture.loadFromFile(piece->GetImage())) {
                    sf::Sprite pieceSprite(pieceTexture);
                    pieceSprite.setPosition(j * squareSize, i * squareSize);
                    window->draw(pieceSprite);
                }
#elif defined(CONSOLE)
                if (piece->getPlayer() == 1) {
                    std::cout << "\033[31m" << piece->getSymbol() << "\033[0m" << ' ';
                }
                else {
                    std::cout << "\033[32m" << piece->getSymbol() << "\033[0m" << ' ';
                }
                
            }
            else {
                std::cout << ". ";
#endif
                
            }
        }
       
    }
#ifdef CONSOLE
    std::cout << std::endl <<"\033[32m" << "       Player 2     " << "\033[0m" << std::endl;
#endif // defined(CONSOLE)
}

void Board::initializeGame() {
    // Clear the board and resize it to 8x8
    grid.clear();
    grid.resize(8, std::vector<Piece*>(8, nullptr));

    // Set up player 1 (white pieces)
    grid[0][0] = new Rook("../../../img/Chess_rlt60.png",    'R', { 0, 0 }, 1);  // A1
    grid[0][1] = new Knight("../../../img/Chess_nlt60.png",  'L', { 1, 0 }, 1);  // B1
    grid[0][2] = new Bishop("../../../img/WhiteBishop.png",  'B', { 2, 0 }, 1);  // C1
    grid[0][3] = new Queen("../../../img/Chess_qlt60.png",   'Q', { 3, 0 }, 1);  // D1
    grid[0][4] = new King("../../../img/Chess_klt60.png",    'K', { 4, 0 }, 1);  // E1
    grid[0][5] = new Bishop("../../../img/WhiteBishop.png",  'B', { 5, 0 }, 1);  // F1
    grid[0][6] = new Knight("../../../img/Chess_nlt60.png",  'L', { 6, 0 }, 1);  // G1
    grid[0][7] = new Rook("../../../img/Chess_rlt60.png",    'R', { 7, 0 }, 1);  // H1

    // White pawns
    for (int col = 0; col < 8; ++col) {
        grid[1][col] = new Pawn("../../../img/Chess_plt60.png", 'P', { col, 1 }, 1);  // Pawns in row 2
    }

    // Set up player 2 (black pieces)
    grid[7][0] = new Rook("../../../img/Chess_rdt60.png",  'R',  { 0, 7 }, 2);  // A8
    grid[7][1] = new Knight("../../../img/Chess_ndt60.png",'L',  { 1, 7 }, 2);  // B8
    grid[7][2] = new Bishop("../../../img/BlackBishop.png",'B',  { 2, 7 }, 2);  // C8
    grid[7][3] = new Queen("../../../img/Chess_qdt60.png", 'Q',  { 3, 7 }, 2);  // D8
    grid[7][4] = new King("../../../img/Chess_kdt60.png",  'K',  { 4, 7 }, 2);  // E8
    grid[7][5] = new Bishop("../../../img/BlackBishop.png",'B',  { 5, 7 }, 2);  // F8
    grid[7][6] = new Knight("../../../img/Chess_ndt60.png",'L',  { 6, 7 }, 2);  // G8
    grid[7][7] = new Rook("../../../img/Chess_rdt60.png",  'R',  { 7, 7 }, 2);  // H8

    // Black pawns
    for (int col = 0; col < 8; ++col) {
        grid[6][col] = new Pawn("../../../img/Chess_pdt60.png", 'P', { col, 6 }, 2);  // Pawns in row 7
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

Piece* Board::GetPiece(std::pair<int,int> coord) {
    int col = coord.first;
    int row = coord.second;
    if (col >= 0 && col < cols && row >= 0 && row < rows) {
        return grid[row][col]; // Notice it's [row][col] because grid is row-major
    }
    return nullptr;
}

Piece* Board::GetPieceToPlay() { return PieceToPlay; }

void Board::SetPieceToPlay(Piece& piece) { PieceToPlay = &piece; }

int Board::GetCurrentPlayer() const {
    return currentPlayer;
}

bool Board::isOccupied(int row, int col) const {

    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return true;
    }

    return grid[row][col] != nullptr;
}
#ifdef SFML
sf::RenderWindow* Board::getBoardWindow() { return window; }
void Board::setBoardWindow(sf::RenderWindow& drawWindow) { window = &drawWindow; }
#endif // SFML



bool Board::CanPlay(Piece& piece, const std::pair<int, int> coord) {
    std::pair<int, int> targetCoordinate = coord;
    std::pair<int, int> currentCoordinate = piece.getPosition();
    int currentRow = currentCoordinate.second;
    int currentCol = currentCoordinate.first;
    int targetRow = targetCoordinate.second;
    int targetCol = targetCoordinate.first;

    if (!piece.isValidMove(targetCoordinate)) {
        return false;
    }
    if (dynamic_cast<const Pawn*>(&piece)) {
        int currentRow = piece.getPosition().second;
        int currentCol = piece.getPosition().first;

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


    int r = currentRow + rowStep;
    int c = currentCol + colStep;
    if (piece.getSymbol() != 'L') {
        while (r != targetRow || c != targetCol) {
            if (isOccupied(r, c)) {
                return false;
            }
            r += rowStep;
            c += colStep;
        }
        return true;
    }
    else
    {
        return true;
    }
    
}

void Board::MovePiece(Piece& piece, std::pair<int, int> coord) {
    std::pair<int, int> targetCoordinate = coord;

    if (CanPlay(piece, coord)) {
        std::pair<int, int> currentCoordinate = piece.getPosition();
        int currentRow = currentCoordinate.second;
        int currentCol = currentCoordinate.first;

        // Update the grid
        grid[targetCoordinate.second][targetCoordinate.first] = &piece; // Place piece in new position
        grid[currentRow][currentCol] = nullptr; // Clear old position

        // Update the piece's position
        piece.setPosition(coord);

        PieceToPlay = nullptr;
        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Switch player
    }
    else {
        std::cout << "Invalid move" << std::endl;
        PieceToPlay = nullptr;
    }
}