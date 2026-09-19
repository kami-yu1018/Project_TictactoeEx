#include "DxLib.h"
#include "Scene_Title.h"
#include "main.h"

void Scene_Title::Init()
{
	Exit();
	backgroundImage = LoadGraph("data/background.png");
	titleFont = CreateFontToHandle("メイリオ", 48, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	menuFont = CreateFontToHandle("メイリオ", 32, 2, DX_FONTTYPE_ANTIALIASING_EDGE);
	selectedItem = -1;
	nextscene = NONE;
	// 戻るボタンなど、シーンに入る前から押されていた左ボタンでは決定しない。
	previousLeft = CheckMouseInput(MOUSE_INPUT_LEFT);

	//	seの読み込み
	check_se = LoadSoundMem("data/se/check.mp3");

	//	不透明度は０
	shade_alpha = 0;
	nextGo = 0;
}

void Scene_Title::Update()
{
	// 既存のマウス入力関数を利用する。現在と前回の状態で押した瞬間を判定する。
	const int mouseX = GetMouseX();
	const int mouseY = GetMouseY();
	const bool left = CheckMouseInput(MOUSE_INPUT_LEFT);

	// 決定後は Game が遷移要求を処理するまで、次のクリックを受け付けない。
	if (nextscene == NONE)
	{
		if(!nextGo)
		{
			// メニュー外では選択を外す。項目間の隙間や背景のクリックでは決定しない。
			selectedItem = -1;
			for (int i = 0; i < MENU_COUNT; ++i)
			{
				const int y = MENU_FIRST_Y + i * MENU_INTERVAL;
				if (mouseX >= MENU_LEFT && mouseX <= MENU_RIGHT
					&& mouseY >= y + MENU_TOP_OFFSET && mouseY <= y + MENU_BOTTOM_OFFSET)
				{
					selectedItem = i;
					break;
				}

			}
		}

		//	GAMEに渡す次のシーン変数
		const NextScene destinations[] = { GAME, RULE, QUIT };
		// 項目の上で左ボタンを押した瞬間、次のシーンへ移動してもよいと設定する。
		// 押したまま別の項目へ移動しても決定しない。
		if (selectedItem >= 0 && left && !previousLeft)
		{
			nextGo = 1;

			//	seを鳴らす
			if (se.se_ring == 0)
			{
				se.PlaySe(check_se);
				se.se_ring = 1;
			}
			/*if(shade_alpha>=255)
			{
				const NextScene destinations[] = { GAME, RULE, QUIT };
				nextscene = destinations[selectedItem];
				if (se.se_ring == 0)
				{
					se.PlaySe(check_se);
					se.se_ring = 1;
				}
			}*/
		}
		else
		{
			if(!nextGo)
			{
				se.se_ring = 0;
			}
		}

		//	次のシーンへ移って良いのなら
		if(nextGo)
		{
			//	フェードアウト用画像の不透明度をあげる
			shade_alpha += 5;
			//	不透明度が最大になったら対応する次のシーンへ
			if (shade_alpha >= 255)
			{
				nextscene = destinations[selectedItem];
			}
		}

	}

	// 今回の押下状態を保存し、次フレームの長押し判定に使う。
	previousLeft = left;
}

void Scene_Title::Render()
{
	const unsigned int ink = GetColor(60, 42, 32);
	const unsigned int white = GetColor(255, 255, 255);
	if (backgroundImage >= 0)
	{
		DrawExtendGraph(0, 0, WINDOW_W, WINDOW_H, backgroundImage, FALSE);
	}
	else
	{
		DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(255, 198, 138), TRUE);
	}

	const char* title = "○×ゲーム";
	int width = GetDrawStringWidthToHandle(title, lstrlenA(title), titleFont);
	DrawStringToHandle((WINDOW_W - width) / 2, 230, title, ink, titleFont, white);

	const char* menu[] = { "ゲームスタート", "ゲームルール", "終了" };
	for (int i = 0; i < MENU_COUNT; ++i)
	{
		const int y = MENU_FIRST_Y + i * MENU_INTERVAL;
		const bool selected = i == selectedItem;
		if (selected)
		{
			DrawBox(MENU_LEFT, y + MENU_TOP_OFFSET, MENU_RIGHT, y + MENU_BOTTOM_OFFSET, ink, TRUE);
			// フォントに依存しない右向きの選択矢印。
			DrawTriangle(190, y + 6, 190, y + 32, 210, y + 19, white, TRUE);
		}
		width = GetDrawStringWidthToHandle(menu[i], lstrlenA(menu[i]), menuFont);
		DrawStringToHandle((WINDOW_W - width) / 2, y, menu[i],
			selected ? white : ink, menuFont, selected ? ink : white);
	}
	const char* guide = "マウスで選択　左クリックで決定";
	width = GetDrawStringWidth(guide, lstrlenA(guide));
	DrawString((WINDOW_W - width) / 2, 745, guide, ink);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, shade_alpha);
	DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Scene_Title::Exit()
{
	if (backgroundImage >= 0) DeleteGraph(backgroundImage);
	if (titleFont >= 0) DeleteFontToHandle(titleFont);
	if (menuFont >= 0) DeleteFontToHandle(menuFont);
	backgroundImage = -1;
	titleFont = -1;
	menuFont = -1;
}