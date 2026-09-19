#include "Game.h"
#include "main.h"

void Game::Init()
{
	//	初期化
	RuleObj.Init();
	ResultObj.Init();
	GameObj.Init();
	TitleObj.Init();

	//	最初のシーンはタイトルから
	nowScene = SCENE_TITLE;
	exitRequested = false;
	
}

void Game::Update()
{
	switch (nowScene)
	{
	case SCENE_TITLE:
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
		break;

	case SCENE_GAME:
		GameObj.Update();
		gameResult = GameObj.CheckWin();
		if (gameResult > 0)
		{
			nowScene = SCENE_RESULT;
		}
		break;

	case SCENE_RULE:
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
		break;

	case SCENE_RESULT:
		ResultObj.Update();
		if(ResultObj.nextGo)
		{
			if (ResultObj.nextscene == 1)

			{
				// タイトルへ戻る

				TitleObj.Init();
				GameObj.Init();

				ResultObj.Init();

				nowScene = SCENE_TITLE;

			}

			else if (ResultObj.nextscene == 2)

			{
				// リトライ

				GameObj.Init();

				ResultObj.Init();

				nowScene = SCENE_GAME;

			}
		}

		break;
	}
}

//	描画処理
void Game::Render()
{
	switch (nowScene)
	{
	case SCENE_TITLE:
		TitleObj.Render();
		break;

	case SCENE_GAME:
		GameObj.Render();
		break;

	case SCENE_RULE:
		RuleObj.Render();
		break;

	case SCENE_RESULT:
		ResultObj.Render(gameResult);
		break;
	}
}

void Game::Exit()
{
	// 初期化した画面のリソースを解放する。未接続の Result は初期化・解放しない。
	TitleObj.Exit();
	RuleObj.Exit();
	ResultObj.Exit();
}

bool Game::IsExitRequested() const
{
	return exitRequested;
}