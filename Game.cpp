#include "Game.h"
#include "main.h"

void Game::Init()
{
	Exit();
	//	初期化
	RuleObj.Init();
	ResultObj.Init();
	GameObj.Init();
	TitleObj.Init();

	//	最初のシーンはタイトルから
	nowScene = SCENE_TITLE;
	exitRequested = false;

	//	BGMの読み込み
	bgm = LoadMusicMem("data/bgm.mp3");
}

void Game::Update()
{
	if (check_bgm == 0)
	{
		PlayMusic("data/bgm.mp3", DX_PLAYTYPE_LOOP);
		check_bgm = 1;
	}

	switch (nowScene)
	{
	case SCENE_TITLE:	//	タイトル画面
		TitleObj.Update();
		// タイトルは要求だけを通知し、実際の切り替えは Game が担当する。
		switch (TitleObj.nextscene)
		{
		case Scene_Title::GAME:
			GameObj.OnEnter();
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

	case SCENE_GAME:	//	ゲーム画面
		GameObj.Update();
		gameResult = GameObj.CheckWin();	//	勝敗の決定とリザルトに渡すために結果を変数に入れる
		if (gameResult > 0)
		{
			ResultObj.OnEnter();
			nowScene = SCENE_RESULT;
		}
		break;

	case SCENE_RULE:	//	ルール画面
		RuleObj.Update();

		if (RuleObj.scene_back_frag)
		{
			//	前のシーンを調べる
			switch (backScene)
			{
			case 1:			//	前のシーンがタイトルの時
				nowScene = SCENE_TITLE;
				backScene = 0;
				TitleObj.Init();
				break;
			case 2:			//	前のシーンがゲーム画面の時
				GameObj.OnEnter();
				nowScene = SCENE_GAME;
				break;
			}
		}
		break;

	case SCENE_RESULT:	//	リザルト画面
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
	case SCENE_TITLE:	//	タイトル画面
		TitleObj.Render();
		break;

	case SCENE_GAME:	//	ゲーム画面
		GameObj.Render();
		break;

	case SCENE_RULE:	//	ルール画面
		RuleObj.Render();
		break;

	case SCENE_RESULT:	//	リザルト画面
		ResultObj.Render(gameResult);	//	勝敗を引数に入れる（これによって表示するテキストを変える）
		break;
	}
}

void Game::Exit()
{
	// 全シーンの画像・音声・フォントとBGMを解放する。
	TitleObj.Exit();
	GameObj.Exit();
	RuleObj.Exit();
	ResultObj.Exit();
	StopMusic();
	if (bgm >= 0) DeleteMusicMem(bgm);
	bgm = -1;
	check_bgm = 0;
}

bool Game::IsExitRequested() const
{
	return exitRequested;
}