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
	//	se読み込み
	back_se = LoadSoundMem("data/se/back.mp3");

	//	戻るボタンのフラグの初期化
	scene_back_frag = false;
	
	shade_alpha = 254;
	nextGo = false;
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
//		scene_back_frag = true;
		nextGo = true;
		
		if (se.se_ring == 0)
		{
			se.PlaySe(back_se);
		}
	}
	else
	{
		se.se_ring = 0;
	}

	if (nextGo)
	{
		shade_alpha += 5;
		if (shade_alpha >= 255)
		{
			scene_back_frag = true;
			shade_alpha = 0;
		}
	}
	else
	{
		shade_alpha -= 20;
		if (shade_alpha < 0)
		{
			shade_alpha = 0;
		}
	}
}

void Scene_Rule::Render()
{
	DrawGraph(0, 0, ruleImage, TRUE);
	DrawGraph(20, 20, backImage, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shade_alpha);
	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Scene_Rule::Exit()
{
	DeleteGraph(ruleImage);
}

