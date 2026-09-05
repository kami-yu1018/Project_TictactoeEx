#pragma once
#include"DxLib.h"

class Scene_Game
{
public:

	//　盤面の状態を保持する配列
	int board[7][7] = { 0 };

	int board_size = 3;

	//　マウス座標
	int mouse_pos_x;
	int mouse_pos_y;

	//　マウスの入力状態
	bool mouse_input = false;
	bool key_state = false;

	//　記号を置いた数をカウント
	int count = 0;

	void Init();
	void Update();
	void Render();
	void Exit();
};