#include "pch.h"
#include "Board.h"

// Function to load the chessboard and piece textures
bool loadTextures(sf::Texture& boardTexture, sf::Sprite& boardSprite) {
    if (!boardTexture.loadFromFile("../../../Images/chessboard.png")) {
        MessageBox(nullptr, L"Failed to load chessboard texture!", L"Error", MB_OK | MB_ICONERROR);  // Debug message
        return false;  // Failed to load chessboard texture
    }
    boardSprite.setTexture(boardTexture);  // Set the chessboard sprite
    return true;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML Chess");

    // Chessboard textures
    sf::Texture boardTexture;
    sf::Sprite boardSprite;

    // Load chessboard texture
    if (!loadTextures(boardTexture, boardSprite)) {
        return -1;  // Exit if loading failed
    }

    // Main game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Ensure this closes the window properly
            }
        }

        // Clear the window
        window.clear();

        // Draw the chessboard
        window.draw(boardSprite);

        // Display the window
        window.display();
    }

    return 0;
}