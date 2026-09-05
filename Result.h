#pragma once

#include"DxLib.h"

class Result
{
private:
	int backgroundImage; // 背景画像のハンドル
	int resultImage[2];	// 勝敗画像のハンドル

public:
	int nextscene;	//	次のシーンを示す変数（0:タイトル画面、1:ゲーム画面）

	void Init();	//	初期化
	void Update();	//	更新
	void Render(int playresult);	//	描画（勝敗によって勝ち負けの画像表示を変えるため引数に勝敗を受け取る）
	void Exit();	//	終了
};