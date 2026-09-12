#include "Scene_Rule.h"
#include"main.h"

Scene_Rule::Scene_Rule() 
{
	ruleImage = -1; // ルール画像のハンドルを初期化
	backImage = -1;	//	戻るボタンのハンドルを初期化
}

void Scene_Rule::Init()
{
	//	画像読み込み
	ruleImage = LoadGraph("data/Rule_image.png");
	backImage = LoadGraph("data/back_img.png");

	//	戻るボタンのフラグの初期化
	scene_back_frag = false;

	back_se = LoadSoundMem("data/se/back.mp3");
}

void Scene_Rule::Update()
{
	//	戻るボタンが押されたらシーンを戻す
	//	マウス座標を取得
	int mosueX = GetMouseX();
	int mouseY = GetMouseY();
	//	左クリックされた時の座標が戻るボタンの範囲内であればシーンを戻す
	if (PushMouseInput(MOUSE_INPUT_LEFT)
		&& mosueX >= 20 && mosueX <= 70
		&& mouseY >= 20 && mouseY <= 70)
	{
		scene_back_frag = true;
		
		if (se.se_ring == 0)
		{
			se.PlaySe(back_se);
		}
	}
	else
	{
		se.se_ring = 0;
	}

}

void Scene_Rule::Render()
{
	DrawGraph(0, 0, ruleImage, TRUE);
	DrawGraph(20, 20, backImage, TRUE);
}

void Scene_Rule::Exit()
{
	DeleteGraph(ruleImage);
}

