#pragma once
#include"DxLib.h"

class Scene_Game
{
public:
	//	背景用変数
	int backgroundImage;

	//　盤面の状態を保持する配列
	int board[9][9] = { 0 };
	int draw_player[9][9] = { 0 };

	//　ボードのサイズの初期値
	int board_size = 3;

	//　どちらのターンかの判定
	bool player_turn = true;

	//　マウス座標
	int mouse_pos_x;
	int mouse_pos_y;

	//　マウスの入力状態
	bool mouse_input = false;
	bool key_state = false;

	//　記号を置いた数をカウント
	int count = 0;

	//　勝利に必要な記号の数
	int win_count;

	//　勝者が誰かを判定した数字を入れる用の変数
	int winner = 0;

private:
	//　マークを置く処理をする関数
	bool MarkPlace(int x, int y);
	//　
	bool GetBoardCell(int mouse_pos_x, int mouse_pos_y, int* board_x, int* board_y);

public:

	void Init();
	void Update();
	void Render();
	void Exit();

	//　勝利判定をする関数
	int CheckWin();
};