#include "pch.h"

class Board {
public:
    Board(int rows, int cols);
    void display(sf::RenderWindow& window) const;
    void initializeGame();
    Piece* GetPiece(int col, int row);
    int GetCurrentPlayer() const;

    bool isOccupied(int col, int row) const;

    std::pair<int, int> coordToIndex(const std::string& coord) const;

    bool CanPlay(Piece& piece, std::pair<int, int> target);
    void MovePiece(Piece& piece, std::pair<int, int> target);

    int GetHintNumber();
    void setHintNumber(int value);

private:
    int rows, cols;
    std::vector<std::vector<Piece*>> grid;
    int currentPlayer;
    int hintNumber = 0;
    mutable sf::Texture boardTexture; // Texture for the board
    mutable std::vector<sf::Texture> pieceTextures; // Textures for pieces
};
