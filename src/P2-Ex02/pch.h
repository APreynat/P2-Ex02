#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

#include "resource.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#include "Piece.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <array>
#include <chrono>
#include <thread>
#include <windows.h>
