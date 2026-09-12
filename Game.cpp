#include "Game.h"
#include "main.h"

void Game::Init()
{
	//	初期化
	RuleObj.Init();
	ResultObj.Init();

	//	最初のシーンはタイトルから
	nowScene = SCENE_TITLE;
	// 起動時はタイトルから開始。ルール画像は一度だけ読み込み、戻っても再利用する。
	nowScene = SCENE_TITLE;
	exitRequested = false;
	TitleObj.Init();
	RuleObj.Init();
}

void Game::Update()
{
	if (nowScene == SCENE_TITLE)
	{

	}
	if (nowScene == SCENE_GAME)
	{

	}
	if (nowScene == SCENE_RULE)
	{
		RuleObj.Update();
	}
	if (nowScene == SCENE_RESULT)
	{
		ResultObj.Update();
	// 表示中の画面だけを更新する。遷移した先の Update は次のフレームで呼ぶ。
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
			nowScene = SCENE_RULE;
			break;
		case Scene_Title::QUIT:
			exitRequested = true;
			break;
		case Scene_Title::NONE:
			break;
		}
		break;

	case SCENE_RULE:
		RuleObj.Update();
		// ルール画面の既存の戻るボタンが立てるフラグを利用する。
		if (RuleObj.scene_back_frag)
		{
			TitleObj.Init();
			nowScene = SCENE_TITLE;
		}
		break;

	case SCENE_GAME:
		// 仮画面から B キーで戻れる。本体の実装時はここを Scene_Game に接続する。
		if (CheckHitKey(KEY_INPUT_B))
		{
			TitleObj.Init();
			nowScene = SCENE_TITLE;
		}
		break;
	}
}

void Game::Render()
{
	if (nowScene == SCENE_TITLE)
	{

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
	// 元からあった盤面描画の試作コードは、ゲーム担当との共有用に残す。
	/*for (int j = 0; j < 7; ++j)
	{
		for (int i = 0; i < 7; ++i)
		{
			int x1 = 50 + (700/7) * (i);
			int y1 = 100 + (700 / 7) * (j);
			int x2 = x1 + (700 / 7);
			int y2 = y1 + (700 / 7);
			DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);
		}
	}*/
	// 選ばれている画面だけを描画し、別シーンの描画を重ねない。
	switch (nowScene)
	{
	case SCENE_TITLE:
		TitleObj.Render();
		break;
	case SCENE_RULE:
		RuleObj.Render();
		break;
	case SCENE_GAME:
		// ゲーム本体は他担当のため作らず、遷移確認用の文字だけを表示する。
		DrawString(220, 380, "ゲーム画面（仮）", GetColor(255, 255, 255));
		DrawString(220, 430, "ゲームスタートの遷移を受け付けました", GetColor(255, 255, 255));
		DrawString(220, 480, "B キー：タイトルへ戻る", GetColor(255, 255, 255));
		break;
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