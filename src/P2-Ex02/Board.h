#pragma once
#include "pch.h"

class Board {
public:
#ifdef SFML
    Board(int rows, int cols, sf::RenderWindow& window);
#elif defined CONSOLE
    Board(int rows, int cols);
#endif // SFML

    void display() const;
    void initializeGame();
    Piece* GetPiece(int col, int row);
    Piece* GetPiece(std::pair<int, int> coord);
    Piece* GetPieceToPlay();
    int GetCurrentPlayer() const;
    sf::RenderWindow* getBoardWindow();

    bool isOccupied(int col, int row) const;

    bool CanPlay(Piece& piece, std::pair<int, int> target);
    void MovePiece(Piece& piece, std::pair<int, int> target);

    void setBoardWindow(sf::RenderWindow& drawWindow);
    void SetPieceToPlay(Piece& piece);

private:
    int rows, cols;
    std::vector<std::vector<Piece*>> grid;
    int currentPlayer;
    Piece* PieceToPlay;
#ifdef SFML
    mutable sf::Texture boardTexture; // Texture for the board
    mutable std::vector<sf::Texture> pieceTextures; // Textures for pieces
    sf::RenderWindow* window;
#endif // SFML

    
};
