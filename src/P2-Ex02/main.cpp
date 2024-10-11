#include "pch.h"
#include "Board.h"
#include "TextureManager.h"


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"WinAppClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    if (RegisterClassExW(&wcex) == 0)
        return 0;

    HWND hWnd = CreateWindowW(L"WinAppClass", L"Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    if (hWnd == NULL)
        return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    sf::RenderWindow window(hWnd);

    // Create texture manager and load all textures
    TextureManager textureManager;
    if (!textureManager.loadAllTextures()) {
        MessageBox(nullptr, L"Failed to load chess piece textures!", L"Error", MB_OK | MB_ICONERROR);
        return -1;  // Exit if textures could not be loaded
    }

    // Create a Board object
    Board board;

    // Load chessboard texture
    if (!board.loadSprite()) {
        return -1;  // Exit if loading failed
    }

    // Place white pieces
    board.placePiece(new Rook('W', 'R', textureManager.getTexture('W', "rook"), "A1"), "A1");
    board.placePiece(new Knight('W', 'N', textureManager.getTexture('W', "knight"), "B1"), "B1");
    board.placePiece(new Bishop('W', 'B', textureManager.getTexture('W', "bishop"), "C1"), "C1");
    board.placePiece(new Queen('W', 'Q', textureManager.getTexture('W', "queen"), "D1"), "D1");
    board.placePiece(new King('W', 'K', textureManager.getTexture('W', "king"), "E1"), "E1");
    board.placePiece(new Bishop('W', 'B', textureManager.getTexture('W', "bishop"), "F1"), "F1");
    board.placePiece(new Knight('W', 'N', textureManager.getTexture('W', "knight"), "G1"), "G1");
    board.placePiece(new Rook('W', 'R', textureManager.getTexture('W', "rook"), "H1"), "H1");

    // Place white pawns
    for (char col = 'A'; col <= 'H'; ++col) {
        std::string position = std::string(1, col) + "2"; // E.g., A2, B2, ..., H2
        board.placePiece(new Pawn('W', 'P', textureManager.getTexture('W', "pawn"), position), position);
    }

    // Place black pieces
    board.placePiece(new Rook('B', 'R', textureManager.getTexture('B', "rook"), "A8"), "A8");
    board.placePiece(new Knight('B', 'N', textureManager.getTexture('B', "knight"), "B8"), "B8");
    board.placePiece(new Bishop('B', 'B', textureManager.getTexture('B', "bishop"), "C8"), "C8");
    board.placePiece(new Queen('B', 'Q', textureManager.getTexture('B', "queen"), "D8"), "D8");
    board.placePiece(new King('B', 'K', textureManager.getTexture('B', "king"), "E8"), "E8");
    board.placePiece(new Bishop('B', 'B', textureManager.getTexture('B', "bishop"), "F8"), "F8");
    board.placePiece(new Knight('B', 'N', textureManager.getTexture('B', "knight"), "G8"), "G8");
    board.placePiece(new Rook('B', 'R', textureManager.getTexture('B', "rook"), "H8"), "H8");

    // Place black pawns
    for (char col = 'A'; col <= 'H'; ++col) {
        std::string position = std::string(1, col) + "7"; // E.g., A7, B7, ..., H7
        board.placePiece(new Pawn('B', 'P', textureManager.getTexture('B', "pawn"), position), position);
    }

    // Assuming 'textError' is an sf::Text object for displaying errors
    sf::Text textError;

    std::string selectedPosition; // To track the selected piece position

    // Main game loop
    MSG msg;

    while (window.isOpen()) {
        // Process Windows messages
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                window.close();
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Mouse click handling
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            // Get mouse position relative to the window
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // Convert mouse position to board coordinates (assuming each square is 81x81 pixels)
            int x = abs(mousePos.x / 81); // Column index
            int y = abs(mousePos.y / 81); // Row index

            // Ensure the coordinates are within the bounds of the board (8x8)
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                std::string position = std::string(1, 'A' + x) + std::to_string(8 - y); // Convert to chess notation

                if (selectedPosition.empty()) {
                    // No piece is selected yet, so select a piece at the clicked position
                    int row, col;
                    if (board.getPositionIndices(position, row, col)) {
                        if (board.grid[row][col] != nullptr) {
                            // A piece is present at the clicked position
                            selectedPosition = position;
                            textError.setString("Piece selected at " + position);
                        }
                        else {
                            // No piece is present at the clicked position
                            textError.setString("No piece at selected position.");
                        }
                    }
                }
                else {
                    // A piece is already selected, now attempt to move it to the clicked position
                    if (board.movePiece(selectedPosition, position)) {
                        textError.setString("Moved piece from " + selectedPosition + " to " + position);
                    }
                    else {
                        textError.setString("Invalid move from " + selectedPosition + " to " + position);
                    }

                    // Reset selected piece position after attempting a move
                    selectedPosition.clear();
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw the board and pieces
        board.display(window);

        // Display any error messages
        window.draw(textError);

        // Display the window
        window.display();
    }

    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int notif = HIWORD(wParam);
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    }
    return 0;
}
