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
}

void Result::Update()
{
	//	マウス座標を取得
	int MouseX = GetMouseX();
	int MouseY = GetMouseY();

	//	左クリックしたとき
	if (PushMouseInput(MOUSE_INPUT_LEFT))
	{
		//	タイトルへ戻る
		if (MouseX >= 100 && MouseX <= 700
			&& MouseY >= 400 && MouseY <= 450)
		{
			nextscene = 1;
		}

		//	リトライ
		if (MouseX >= 100 && MouseX <= 700
			&& MouseY >= 500 && MouseY <= 550)
		{
			nextscene = 2;
		}
	}
}

void Result::Render(int playresult)
{
	//	背景画像の描画
	DrawGraph(0, 0, backgroundImage, TRUE);
	if(playresult==1)	//	勝ちの時
	{ 
		DrawGraph(150, 100, resultImage[0], TRUE);
	}
	else if (playresult == 2)	//	負けの時
	{
		DrawGraph(150, 100, resultImage[1], TRUE);
	}

	DrawString(100, 400, "タイトルへ戻る", GetColor(255, 255, 255));
	DrawString(100, 500, "リトライ", GetColor(255, 255, 255));

	DrawFormatString(10, 10, GetColor(255, 255, 255), "%d", nextscene);
}

void Result::Exit()
{
	//	背景画像の解放
	DeleteGraph(backgroundImage);
}