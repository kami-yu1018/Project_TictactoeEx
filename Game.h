#pragma once
#include"DxLib.h"
#include"Scene_Rule.h"

class Game
{
private:
	//	インスタンス
	Scene_Rule RuleObj;

public:
	void Init();
	void Update();
	void Render();
	void Exit();
};