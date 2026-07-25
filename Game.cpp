#include "Game.h"

void Game::Init()
{

}

void Game::Update()
{

}

void Game::Render()
{
	for (int j = 0; j < 7; ++j)
	{
		for (int i = 0; i < 7; ++i)
		{
			int x1 = 50 + (700/7) * (i);
			int y1 = 100 + (700 / 7) * (j);
			int x2 = x1 + (700 / 7);
			int y2 = y1 + (700 / 7);
			DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);
		}
	}

}

void Game::Exit()
{

}