#pragma once
#include "pch.h"

class TextureManager {
public:

    TextureManager();
    ~TextureManager();

    // Loads all piece textures
    bool loadAllTextures();

    // Get the texture for a specific piece type
    const sf::Texture& getTexture(char color, const std::string& pieceType) const;

private:
    map<string, sf::Texture> textures;  // Stores textures for each type of piece
};
