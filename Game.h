#pragma once
#include"DxLib.h"
#include"Scene_Rule.h"
#include"Result.h"
#include"Scene_Title.h"

class Game
{
private:
	// 現在表示する画面だけを管理する。ゲーム画面は本体実装まで仮表示する。
	enum Scene
	{
		SCENE_TITLE,
		SCENE_GAME,
		SCENE_RULE,
	};
	Scene nowScene = SCENE_TITLE;
	bool exitRequested = false; // main に正常終了を依頼するフラグ。
	Scene_Title TitleObj;
	//	インスタンス
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