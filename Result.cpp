// UTF-8 BOMを付け、コンパイラが日本語文字列をShift-JISとして誤読するのを防ぐ。
//	エンディング画面（結果発表）

#include"Result.h"
#include"main.h"

void Result::Init()
{
	Exit();
	se.Reset_SeCheck();
	//	背景画像の読み込み
	backgroundImage = LoadGraph("data/background.png");	//	背景
	resultImage[0] = LoadGraph("data/circle_win.png");	//	〇の勝ち
	resultImage[1] = LoadGraph("data/X_win.png");	//	×の勝ち
	resultImage[2] = LoadGraph("data/draw.png");	//	引き分け

	menuFont = CreateFontToHandle("メイリオ", 32, 2, DX_FONTTYPE_ANTIALIASING_EDGE);

	//	関数の初期化
	nextscene = 0;
	shade_alpha = 255;

	nextGo = false;

	//	SEの読み込み
	check_se = LoadSoundMem("data/se/check.mp3");

	text_pos_y = 100.0f;
	move_speed = -0.5f;

	text_alpha = 255;
	alpha_speed = -2;
	OnEnter();
}

void Result::OnEnter()
{
	previousLeft = CheckMouseInput(MOUSE_INPUT_LEFT);
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
	TextAnimation();
	const bool left = CheckMouseInput(MOUSE_INPUT_LEFT);
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

	if (nextscene == 0 && left && !previousLeft)
	{
		if (selectedItem == 0)
		{
			nextscene = 1;
			if (se.se_ring == 0)
			{
				se.PlaySe(check_se);
				se.se_ring = 1;
			}
		}
		else if (selectedItem == 1)
		{
			nextscene = 2;
			se.PlaySe(check_se);
			se.se_ring = 1;
		}
	}
	if (!nextGo)
	{
		se.se_ring = 0;
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
	previousLeft = left;
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, text_alpha);
	if (playresult == 1)
	{
		DrawGraph(150, text_pos_y, resultImage[0], TRUE);
	}
	else if (playresult == 2)
	{
		DrawGraph(150, text_pos_y, resultImage[1], TRUE);
	}
	else if (playresult == Scene_Game::DRAW)
	{
		DrawGraph(150, text_pos_y, resultImage[2], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	const char* menu[] = { "タイトルに戻る","リトライ" };
	//---------------------------------
	// タイトルへ戻る
	//---------------------------------
	if (selectedItem == 0)
	{
		DrawBox(100, 400, 700, 450, GetColor(0, 0, 0), TRUE);

		DrawTriangle(70, 410, 70, 440, 90, 425, GetColor(255, 255, 255), TRUE);

		DrawStringToHandle(120, 410, menu[0], GetColor(255, 255, 255),menuFont);
	}
	else
	{
		DrawStringToHandle(120, 410, menu[0], GetColor(0, 0, 0), menuFont);
	}

	//---------------------------------
	// リトライ
	//---------------------------------
	if (selectedItem == 1)
	{
		DrawBox(100, 500, 700, 550, GetColor(0, 0, 0), TRUE);

		DrawTriangle(70, 510, 70, 540, 90, 525, GetColor(255, 255, 255), TRUE);

		DrawStringToHandle(120, 510, menu[1], GetColor(255, 255, 255),menuFont);
	}
	else
	{
		DrawStringToHandle(120, 510, menu[1], GetColor(0, 0, 0), menuFont);
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

void Result::TextAnimation()
{
	//	不透明度の変動
	text_alpha += alpha_speed;

	if (text_alpha < 125)
	{
		alpha_speed = 2;
	}

	if (text_alpha > 255)
	{
		alpha_speed = -2;
	}

	//	座標の移動
	text_pos_y += move_speed;

	if (text_pos_y < 80.0)
	{
		move_speed = 0.5f;
	}
	else if (text_pos_y > 120.0f)
	{
		move_speed = -0.5f;
	}
	if (backgroundImage >= 0) DeleteGraph(backgroundImage);
	backgroundImage = -1;
	for (int& image : resultImage)
	{
		if (image >= 0) DeleteGraph(image);
		image = -1;
	}
	if (menuFont >= 0) DeleteFontToHandle(menuFont);
	if (check_se >= 0) DeleteSoundMem(check_se);
	menuFont = -1;
	check_se = -1;
}