#pragma once
#include"DxLib.h"
#include"Scene_Title.h"
#include"Scene_Game.h"
#include"Scene_Rule.h"
#include"Result.h"
#include"Scene_Title.h"

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

	int backScene = 0;	//	前のシーンを入れておく変数（ルール画面からタイトル、ゲーム画面に戻る時に使う　１：タイトル　２：ゲーム）
	int gameResult = 0;	//	勝敗

	bool exitRequested = false; // main に正常終了を依頼するフラグ。
	//	インスタンス
	Scene_Title TitleObj;
	Scene_Rule RuleObj;
	Result ResultObj;

public:
	void Init();
	void Update();
	void Render();
	void Exit();

	// true の場合、main がループを抜けて終了処理を行う。
	bool IsExitRequested() const;
};