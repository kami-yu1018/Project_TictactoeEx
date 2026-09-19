//	エンディング画面（結果発表）

#include"Result.h"
#include"main.h"

void Result::Init()
{
	//	背景画像の読み込み
	backgroundImage = LoadGraph("data/background.png");	//	背景
	resultImage[0] = LoadGraph("data/win_text.png");	//	勝ち
	resultImage[1] = LoadGraph("data/lose_text.png");	//	負け

	//	関数の初期化
	nextscene = 0;
	shade_alpha = 255;
	nextGo = false;
}

//void Result::Update()
//{
//	//	マウス座標を取得
//	int MouseX = GetMouseX();
//	int MouseY = GetMouseY();
//
//	//	左クリックしたとき
//	if (PushMouseInput(MOUSE_INPUT_LEFT))
//	{
//		//	タイトルへ戻る
//		if (MouseX >= 100 && MouseX <= 700
//			&& MouseY >= 400 && MouseY <= 450)
//		{
//			nextscene = 1;
//		}
//
//		//	リトライ
//		if (MouseX >= 100 && MouseX <= 700
//			&& MouseY >= 500 && MouseY <= 550)
//		{
//			nextscene = 2;
//		}
//	}
//}

void Result::Update()
{
	int MouseX = GetMouseX();
	int MouseY = GetMouseY();

	selectedItem = -1;

	// タイトルへ戻る
	if (MouseX >= 100 && MouseX <= 700 &&
		MouseY >= 400 && MouseY <= 450)
	{
		selectedItem = 0;
	}

	// リトライ
	if (MouseX >= 100 && MouseX <= 700 &&
		MouseY >= 500 && MouseY <= 550)
	{
		selectedItem = 1;
	}

	if (PushMouseInput(MOUSE_INPUT_LEFT))
	{
		if (selectedItem == 0)
		{
			nextscene = 1;
		}
		else if (selectedItem == 1)
		{
			nextscene = 2;
		}
	}

	//	フェードイン、アウト
	if (nextscene > 0)
	{
		shade_alpha += 5;
		//	不透明度が最大になったら次のシーンへ行ってよし
		if (shade_alpha >= 255)
		{
			nextGo = true;
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

//void Result::Render(int playresult)
//{
//	//	背景画像の描画
//	DrawGraph(0, 0, backgroundImage, TRUE);
//	if(playresult==1)	//	勝ちの時
//	{ 
//		DrawGraph(150, 100, resultImage[0], TRUE);
//	}
//	else if (playresult == 2)	//	負けの時
//	{
//		DrawGraph(150, 100, resultImage[1], TRUE);
//	}
//
//	DrawString(100, 400, "タイトルへ戻る", GetColor(255, 255, 255));
//	DrawString(100, 500, "リトライ", GetColor(255, 255, 255));
//
//	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", nextscene);
//}

void Result::Render(int playresult)
{

	DrawGraph(0, 0, backgroundImage, TRUE);

	if (playresult == 1)
	{
		DrawGraph(150, 100, resultImage[0], TRUE);
	}
	else if (playresult == 2)
	{
		DrawGraph(150, 100, resultImage[1], TRUE);
	}
	//---------------------------------
	// タイトルへ戻る
	//---------------------------------
	if (selectedItem == 0)
	{
		DrawBox(100, 400, 700, 450, GetColor(0, 0, 0), TRUE);

		DrawTriangle(70, 410, 70, 440, 90, 425, GetColor(255, 255, 255), TRUE);

		DrawString(120, 410, "タイトルへ戻る", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(120, 410, "タイトルへ戻る", GetColor(0, 0, 0));
	}

	//---------------------------------
	// リトライ
	//---------------------------------
	if (selectedItem == 1)
	{
		DrawBox(100, 500, 700, 550, GetColor(0, 0, 0), TRUE);

		DrawTriangle(70, 510, 70, 540, 90, 525, GetColor(255, 255, 255), TRUE);

		DrawString(120, 510, "リトライ", GetColor(255, 255, 255));
	}
	else
	{
		DrawString(120, 510, "リトライ", GetColor(0, 0, 0));
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shade_alpha);
	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Result::Exit()
{
	//	背景画像の解放
	DeleteGraph(backgroundImage);
}