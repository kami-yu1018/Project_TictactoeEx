#include "Game.h"
#include "main.h"

void Game::Init()
{
	//	初期化
	RuleObj.Init();
	ResultObj.Init();
	TitleObj.Init();

	//	最初のシーンはタイトルから
	nowScene = SCENE_TITLE;
	exitRequested = false;
	
}

void Game::Update()
{
	if (nowScene == SCENE_TITLE)
	{
		TitleObj.Update();
		// タイトルは要求だけを通知し、実際の切り替えは Game が担当する。
		switch (TitleObj.nextscene)
		{
		case Scene_Title::GAME:
			nowScene = SCENE_GAME;
			break;
		case Scene_Title::RULE:
			// 前回の「戻る」要求を消してから、既存のルール画面へ移る。
			RuleObj.scene_back_frag = false;
			backScene = 1;
			nowScene = SCENE_RULE;
			break;
		case Scene_Title::QUIT:
			exitRequested = true;
			break;
		case Scene_Title::NONE:
			break;
		}
	}
	if (nowScene == SCENE_GAME)
	{

	}
	if (nowScene == SCENE_RULE)
	{
		RuleObj.Update();
		
		if (RuleObj.scene_back_frag)
		{
			switch (backScene)
			{
			case 1:			//	前のシーンがタイトルの時
				nowScene = SCENE_TITLE;
				backScene = 0;
				TitleObj.Init();
				break;
			case 2:			//	前のシーンがゲーム画面の時
				nowScene = SCENE_GAME;
				break;
			}
		}
	}
	if (nowScene == SCENE_RESULT)
	{
		ResultObj.Update();
	
	}
}

void Game::Render()
{
	if (nowScene == SCENE_TITLE)
	{
		TitleObj.Render();
	}
	if (nowScene == SCENE_GAME)
	{

	}
	if (nowScene == SCENE_RULE)
	{
		RuleObj.Render();
	}
	if (nowScene == SCENE_RESULT)
	{
		ResultObj.Render(gameResult);

	}
}

void Game::Exit()
{
	// 初期化した画面のリソースを解放する。未接続の Result は初期化・解放しない。
	TitleObj.Exit();
	RuleObj.Exit();
}

bool Game::IsExitRequested() const
{
	return exitRequested;
}