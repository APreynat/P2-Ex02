#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

// Loads all piece textures
bool TextureManager::loadAllTextures() {
    // Load white piece textures
    if (!textures["white_pawn"].loadFromFile("../../../Images/white_pawn.png") ||
        !textures["white_rook"].loadFromFile("../../../Images/white_rook.png") ||
        !textures["white_knight"].loadFromFile("../../../Images/white_knight.png") ||
        !textures["white_bishop"].loadFromFile("../../../Images/white_bishop.png") ||
        !textures["white_queen"].loadFromFile("../../../Images/white_queen.png") ||
        !textures["white_king"].loadFromFile("../../../Images/white_king.png")) {
        return false;  // Error loading white piece textures
    }

    // Load black piece textures
    if (!textures["black_pawn"].loadFromFile("../../../Images/black_pawn.png") ||
        !textures["black_rook"].loadFromFile("../../../Images/black_rook.png") ||
        !textures["black_knight"].loadFromFile("../../../Images/black_knight.png") ||
        !textures["black_bishop"].loadFromFile("../../../Images/black_bishop.png") ||
        !textures["black_queen"].loadFromFile("../../../Images/black_queen.png") ||
        !textures["black_king"].loadFromFile("../../../Images/black_king.png")) {
        return false;  // Error loading black piece textures
    }

    return true;  // All textures loaded successfully
}

 // Get the texture for a specific piece type
const sf::Texture& TextureManager::getTexture(char color, const std::string& pieceType) const {
    std::string key = (color == 'W' ? "white_" : "black_") + pieceType;
    return textures.at(key);
}
