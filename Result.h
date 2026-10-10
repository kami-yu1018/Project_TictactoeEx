#pragma once

#include"DxLib.h"
#include"Sound.h"

class Result
{
private:
	int backgroundImage = -1; // 背景画像のハンドル
	int resultImage[3] = { -1, -1, -1 };	// 勝敗画像のハンドル

	int menuFont = -1;

	int selectedItem = -1;
	bool previousLeft = false;

	static constexpr int MENU_LEFT = 100;
	static constexpr int MENU_RIGHT = 700;
	static constexpr int MENU1_TOP = 400;
	static constexpr int MENU1_BOTTOM = 450;
	static constexpr int MENU2_TOP = 500;
	static constexpr int MENU2_BOTTOM = 550;

	//	SE
	Se se;
	int check_se = -1;

	float text_pos_y;		//	アニメーションさせるテキストの座標
	float move_speed = -1;		//	移動スピード

	int text_alpha = 255;		//	タイトル画面の不透明度調整用変数
	int alpha_speed = -2;		//	不透明度調節速度変更（各最低、最高値到達時に±を変更する）

public:
	int nextscene;	//	次のシーンを示す変数（1:タイトル画面、2:ゲーム画面）
	bool nextGo;	//	次のシーンに移動してよいかどうかのフラグ

	int shade_alpha;	//	アニメーション用変数

	void OnEnter(); // Ignore the click held when this scene becomes active.
	void Init();	//	初期化
	void Update();	//	更新
	void Render(int playresult);	//	描画（勝敗によって勝ち負けの画像表示を変えるため引数に勝敗を受け取る）
	void Exit();	//	終了

	void TextAnimation();
};