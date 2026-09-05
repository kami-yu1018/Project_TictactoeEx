#pragma once
#include"DxLib.h"
#include"Scene_Title.h"
#include"Scene_Game.h"
#include"Scene_Rule.h"
#include"Result.h"

class Game
{
	enum Scene
	{
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_RULE,
		SCENE_RESULT,
	};

	Scene nowScene;	//	現在のシーン

	int backScene = 0;	//	前のシーンを入れておく変数（ルール画面からタイトル、ゲーム画面に戻る時に使う）
	int gameResult = 0;	//	勝敗

private:
	//	インスタンス
	Scene_Rule RuleObj;
	Result ResultObj;

public:
	void Init();
	void Update();
	void Render();
	void Exit();
};