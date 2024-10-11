#pragma once

#include <SFML/Graphics.hpp>

#include <windows.h>

#include "resource.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#include "ChessPiece.h"
#include <string>
#include <iostream>
#include <map>

#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "knight.h"
#include "Rook.h"
#include "Pawn.h"

using namespace std;