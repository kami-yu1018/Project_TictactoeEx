#include "Game.h"

void Game::Init()
{
	//	初期化
	RuleObj.Init();
	ResultObj.Init();

	//	最初のシーンはタイトルから
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
	}
}

void Game::Exit()
{

}