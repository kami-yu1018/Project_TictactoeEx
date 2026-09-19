#pragma once

#include"DxLib.h"

class Result
{
private:
	int backgroundImage; // 背景画像のハンドル
	int resultImage[2];	// 勝敗画像のハンドル

	int selectedItem = -1;

	static constexpr int MENU_LEFT = 100;
	static constexpr int MENU_RIGHT = 700;
	static constexpr int MENU1_TOP = 400;
	static constexpr int MENU1_BOTTOM = 450;
	static constexpr int MENU2_TOP = 500;
	static constexpr int MENU2_BOTTOM = 550;


public:
	int nextscene;	//	次のシーンを示す変数（1:タイトル画面、2:ゲーム画面）
	bool nextGo;	//	次のシーンに移動してよいかどうかのフラグ

	int shade_alpha;	//	アニメーション用変数

	void Init();	//	初期化
	void Update();	//	更新
	void Render(int playresult);	//	描画（勝敗によって勝ち負けの画像表示を変えるため引数に勝敗を受け取る）
	void Exit();	//	終了
};