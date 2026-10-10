#include "Scene_Rule.h"
#include"main.h"

Scene_Rule::Scene_Rule() 
{
	ruleImage = -1; // ルール画像のハンドルを初期化
	backImage = -1;	//	戻るボタンのハンドルを初期化
}

void Scene_Rule::Init()
{
	Exit();
	se.Reset_SeCheck();
	//	画像読み込み
	ruleImage = LoadGraph("data/Rule_image.png");
	backImage = LoadGraph("data/back_img.png");
	//	se読み込み
	back_se = LoadSoundMem("data/se/back.mp3");

	//	戻るボタンのフラグの初期化
	scene_back_frag = false;
	
	shade_alpha = 254;
	nextGo = false;

	count = 30;
	graphSwithc = true;
}

void Scene_Rule::Update()
{
	//	戻るボタンのアニメーション
	Animation();

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
		//	SEがなっていなければ鳴らす
		if (se.se_ring == 0)
		{
			se.PlaySe(back_se);
			se.se_ring = 1;
		}
	}
	else
	{
		//	それ以外の場合はSEを鳴らさない
		se.se_ring = 0;
	}

	//	次のシーンに移る際に画面をフェード暗転させる
	if (nextGo)
	{
		shade_alpha += 5;
		if (shade_alpha >= 255)
		{
			scene_back_frag = true;
			nextGo = false;

		}
	}
	//	次のシーンにいかないとき（主にシーン始まり）の時はフェード明転させる
	else
	{
		shade_alpha -= 20;
		if (shade_alpha < 0)
		{
			shade_alpha = 0;
		}
		scene_back_frag = false;
	}
}

void Scene_Rule::Render()
{
	DrawGraph(0, 0, ruleImage, TRUE);	//	ルール画像
	//	戻るボタン
	if(graphSwithc)
	{
		DrawGraph(20, 20, backImage, TRUE);
	}

	//	暗転
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shade_alpha);
	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Scene_Rule::Exit()
{
	//	解放
	if (ruleImage >= 0) DeleteGraph(ruleImage);
	if (backImage >= 0) DeleteGraph(backImage);
	if (back_se >= 0) DeleteSoundMem(back_se);
	ruleImage = -1;
	backImage = -1;
	back_se = -1;
}

//	アニメーション
void Scene_Rule::Animation()
{
	//	カウントによって戻るボタンの表示非表示を切り替える
	count--;
	if (count < 0)
	{
		if (graphSwithc == true)
		{
			graphSwithc = false;
			count = 30;
		}
		else
		{
			graphSwithc = true;
			count = 30;
		}
	}
}
