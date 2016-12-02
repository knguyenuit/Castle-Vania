#pragma once
#include <iostream>
#include "CastleVania.h"

using namespace CastleVania;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CViewWindows::m_hInstance = hInstance;
	CCastleVania* game = new CCastleVania();
	game->Run();
}