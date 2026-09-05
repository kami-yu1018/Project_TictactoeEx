#include "main.h"

int mouseFrame_left;
int mouseFrame_right;
//------------------------------------------------------------------------------
//	WinMain
//------------------------------------------------------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//===============================================
	//	初期化処理
	//===============================================
	//	ログの書き出しを無効化
	SetOutApplicationLogValidFlag(FALSE);

	//	ウィンドウモードの設定
	ChangeWindowMode(TRUE);

	//	ウィンドウサイズとカラービットの設定
	SetGraphMode(WINDOW_W, WINDOW_H, 32);

	//	ウィンドウのタイトル
	SetMainWindowText(TEXT("Test"));

	//	背景色の設定
	SetBackgroundColor(0, 0, 0);

	//	ＤＸライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;		//	エラーが起きたら直ちに終了
	}

	//	ウィンドウ描画モード設定
	SetDrawScreen(DX_SCREEN_BACK);

	Game game_obj;

	game_obj.Init();

	//===============================================
	//	ゲームループ
	//===============================================
	while (ProcessMessage() == 0)
	{

		//	リフレッシュレートを設定するための処理
		clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

		//	マウスカーソル表示設定
		SetMouseDispFlag(TRUE);

		//	printfDxの初期化
		clsDx();

		//	画面上の描画を初期化
		ClearDrawScreen();

		game_obj.Update();
		game_obj.Render();

		//	マウスが押されたらカウント用変数を増やす
		if (CheckMouseInput(MOUSE_INPUT_LEFT))
		{
			mouseFrame_left++;
		}
		else
		{
			mouseFrame_left = 0;
		}

		if (CheckMouseInput(MOUSE_INPUT_RIGHT))
		{
			mouseFrame_right++;
		}
		
		
		else
		{
			mouseFrame_right=0;
		}


		//	リフレッシュレートが一定になるまで待つ処理
		while (clock() < check_fps) {}

		//	裏画面の描画を表に反映
		ScreenFlip();

		//	ループを抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			return 0;
		}
	}

	//===============================================
	//	終了処理
	//===============================================

	//	ＤＸライブラリ使用の終了処理
	DxLib_End();

	//	ソフトの終了
	return 0;
}


/// <summary>
/// マウスが押されているかどうかを判定し取得
/// </summary>
/// <param name="button"></param>
/// <returns></returns>
bool CheckMouseInput(int button)
{
	if (GetMouseInput() & button)
	{
		return true;
	}
	return false;
}

/// <summary>
/// マウスが押された瞬間を取得
/// </summary>
/// <param name="button"></param>
/// <returns></returns>
bool PushMouseInput(int button)
{
	if (button & MOUSE_INPUT_LEFT)
	{
		if (mouseFrame_left == 1)
		{
			return true;
		}
	}
	if (button & MOUSE_INPUT_RIGHT)
	{
		if (mouseFrame_right == 1)
		{
			return true;
		}
	}
	return false;
}


/// <summary>
///	マウス座標の取得
/// </summary>
/// <returns></returns>
int GetMouseX()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	return mouseX;
}
int GetMouseY()
{
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	return mouseY;
}