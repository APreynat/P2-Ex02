#include "pch.h"
#include "main.h"
#include "Board.h"
#include "SFMLUtility.h"
//sf::RenderWindow* window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
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
    Board board(8, 8);
    board.initializeGame();
    SFMLUtility sfmlUtility;
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        // Handle error: font not loaded
        return -1;
    }
    sf::Text textX = sfmlUtility.createText(font, 24, sf::Color::Green, { 530, 10 });
    sf::Text textY = sfmlUtility.createText(font, 24, sf::Color::Green, { 530, 40 });
    sf::Text textPlayer = sfmlUtility.createText(font, 24, sf::Color::Green, { 530, 70 });
    sf::Text textError = sfmlUtility.createText(font, 24, sf::Color::Green, { 530,100 });
    

    // Set text properties
    
    MSG msg;
    // Step 1: Create a transparent square
    sf::RectangleShape hoverSquare(sf::Vector2f(64.f, 64.f)); // 64x64 grid square size
    hoverSquare.setFillColor(sf::Color(255, 255, 255, 100));  // White with transparency (alpha = 100)
    hoverSquare.setOutlineColor(sf::Color::Transparent);      // No outline

    while (window.isOpen()) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
           
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                // Get mouse position relative to the window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Convert mouse position to board coordinates
                int x = abs(mousePos.x / 64); // Assuming each square is 64x64 pixels
                int y = abs(mousePos.y / 64);

                // Ensure the coordinates are within the bounds of the board
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (board.GetPieceToPlay() == nullptr) {
                        Piece* piece = board.GetPiece(x, y);
                        if (piece == nullptr || piece->getPlayer() != board.GetCurrentPlayer()) {
                            textError.setString("no piece selected");
                        }
                        else {
                            board.SetPieceToPlay(*piece);
                        }
                    }
                    else {
                        Piece* piece = board.GetPiece(x, y);
                        if (piece == nullptr) {
                            if (!board.CanPlay(*board.GetPieceToPlay(), std::pair<int, int>{x, y})) {
                                textError.setString("wrong emplacement : " + std::to_string(x) + ";" + std::to_string(y));
                            }
                            board.MovePiece(*board.GetPieceToPlay(), std::pair<int, int>{x, y});
                        }
                        else if (piece != board.GetPieceToPlay() && piece->getPlayer() != board.GetCurrentPlayer()) {
                            board.MovePiece(*board.GetPieceToPlay(), piece->getPosition());
                        }
                    }
                }
            }

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Step 2: Update the hover square based on the mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = abs(mousePos.x / 64);
        int y = abs(mousePos.y / 64);

        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            hoverSquare.setPosition(static_cast<float>(x * 64), static_cast<float>(y * 64));
        }

        textX.setString("Current X position (col): " + std::to_string(x));
        textY.setString("Current Y position (row): " + std::to_string(y));
        textPlayer.setString("Current player (1 = White & 2 = Black): " + std::to_string(board.GetCurrentPlayer()));

        // Clear the window
        window.clear();
        // Draw the chessboard
        board.display(window);
        // Draw the hover square
        window.draw(hoverSquare);
        // Draw the text
        window.draw(textX);
        window.draw(textY);
        window.draw(textPlayer);
        window.draw(textError);
        // Display the contents
        window.display();
    }

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

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
