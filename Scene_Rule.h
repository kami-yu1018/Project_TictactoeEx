#pragma once

#include"DxLib.h"

class Scene_Rule
{
	// メンバ変数
	int ruleImage; // ルール画像のハンドル

public:
	Scene_Rule();	//	コンストラクタ

	void Init();	//	初期化
	void Update();	//	更新
	void Render();	//	描画
	void Exit();	//	終了

	bool Scene_back_flag();	//	シーン切り替えフラグ（TRUEの時前のシーンへ戻る）
};