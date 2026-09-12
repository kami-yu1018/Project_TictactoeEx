#pragma once

#include"DxLib.h"
#include"Sound.h"

class Scene_Rule
{
	// メンバ変数
	int ruleImage; // ルール画像のハンドル
	int backImage; // 戻るボタンのハンドル

	Se se;
	int back_se;	//	SE

public:
	bool scene_back_frag = 0;	//	戻るボタンが押されたかどうかのフラグ

	Scene_Rule();	//	コンストラクタ

	void Init();	//	初期化
	void Update();	//	更新
	void Render();	//	描画
	void Exit();	//	終了
};