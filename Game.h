#pragma once
#include"DxLib.h"
#include"Scene_Rule.h"
#include"Result.h"

class Game
{
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