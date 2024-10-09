#include "pch.h"
#include "main.h"
#include "Board.h"
//sf::RenderWindow* window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = nullptr;
	wcex.lpszClassName  = L"WinAppClass";
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if ( RegisterClassExW(&wcex)==0 )
		return 0;

	HWND hWnd = CreateWindowW(L"WinAppClass", L"Title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	if ( hWnd==NULL )
		return 0;

	//window = new sf::RenderWindow(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	sf::RenderWindow window(hWnd);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	Board board(8, 8);
	board.initializeGame();
	MSG msg;
	while (window.isOpen()) {
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				// Get mouse position relative to the window
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);

				// Convert mouse position to board coordinates
				int x = abs( mousePos.x / 64); // Assuming each square is 64x64 pixels
				int y = abs(mousePos.y / 64);

				// Ensure the coordinates are within the bounds of the board
				if (x >= 0 && x < 8 && y >= 0 && y < 8) {
					Piece* piece = board.GetPiece(x, y);  // Get the piece at the clicked position
					if (piece != nullptr) {
						// Example move logic: move piece to the next square down (this needs to be replaced with actual logic)
						std::pair<int, int> targetPosition = { x, y + 1 };  // Move down by one row as an example
						if (y + 1 < 8) {
							board.MovePiece(*piece, targetPosition);
						}
					}
				}
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Update window
		window.clear();
		board.display(window);
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
