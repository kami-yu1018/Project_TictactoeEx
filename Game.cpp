#include "Game.h"

void Game::Init()
{

}

void Game::Update()
{
	//　マウスカーソルの座標を取得
	GetMousePoint(&mouse_pos_x, &mouse_pos_y);

	//　マウスの入力状態を取得
	mouse_input = GetMouseInput();

	//　入力されていないとき
	if (key_state == false)
	{
		//　左クリックが押されたら
		if (mouse_input & MOUSE_INPUT_LEFT)
		{
			//　カウントを増やす
			count++;
		}
	}

	//　盤面のサイズを制限
	if (board_size >= 7)
	{
		board_size = 7;
	}

	//　盤面のサイズを更新
	if (count >= 9 && count < 25)
	{
		board_size = 5;
	}
	else if (count >= 25 && count < 49)
	{
		board_size = 7;
	}

	//　マウスの長押し入力の防止
	if (mouse_input == true)
	{
		key_state = true;
	}
	else
	{
		key_state = false;
	}
}

void Game::Render()
{
	for (int j = 0; j < board_size; ++j)
	{
		for (int i = 0; i < board_size; ++i)
		{
			int x1 = 50 + (700 / board_size) * (i);
			int y1 = 100 + (700 / board_size) * (j);
			int x2 = x1 + (700 / board_size);
			int y2 = y1 + (700 / board_size);
			DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);
		}
	}

	DrawFormatString(50, 50, GetColor(255, 255, 255), "Count: %d", count);
}

void Game::Exit()
{

}