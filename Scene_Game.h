#pragma once
#include"DxLib.h"
#include"Sound.h"

class Scene_Game
{
public:
	// 勝敗結果: 0は継続、1/2は勝者、3は最終盤面での引き分け。
	static constexpr int DRAW = 3;
	//	背景用変数
	int backgroundImage = -1;

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
	int mouse_input = 0;
	bool key_state = false;

	//　記号を置いた数をカウント
	int count = 0;

	//　勝利に必要な記号の数
	int win_count;

	//　勝者が誰かを判定した数字を入れる用の変数
	int winner = 0;

	//	SE
	Se se;
	int check_se = -1;

private:
	//　マークを置く処理をする関数
	bool MarkPlace(int x, int y);
	//　
	bool GetBoardCell(int mouse_pos_x, int mouse_pos_y, int* board_x, int* board_y);

public:

	void Init();
	void OnEnter(); // Ignore the click held when this scene becomes active.
	void Update();
	void Render();
	void Exit();

	//　勝利判定をする関数
	int CheckWin();
};