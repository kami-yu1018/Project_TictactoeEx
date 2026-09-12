#pragma once

#include"DxLib.h"

class Scene_Title
{
private:
	// DxLib が返す画像・フォントの番号。-1 はまだ読み込んでいない状態。
	int backgroundImage = -1;
	int titleFont = -1;
	int menuFont = -1;

	// マウスが重なっている項目。-1:選択なし、0:スタート、1:ルール、2:終了。
	int selectedItem = -1;

	// 前フレームの左ボタン状態。押した瞬間だけ決定し、押しっぱなしを防ぐ。
	bool previousLeft = false;

	// 描画とクリック判定で同じ座標を使い、見た目と反応範囲を一致させる。
	static constexpr int MENU_LEFT = 165;
	static constexpr int MENU_RIGHT = 635;
	static constexpr int MENU_FIRST_Y = 420;
	static constexpr int MENU_INTERVAL = 90;
	static constexpr int MENU_TOP_OFFSET = -14;
	static constexpr int MENU_BOTTOM_OFFSET = 54;
	static constexpr int MENU_COUNT = 3;

public:
	// Game に渡す遷移要求。タイトル自身は画面の切り替えや終了を実行しない。
	enum NextScene
	{
		NONE, // まだ決定していない。
		GAME, // ゲームスタート。
		RULE, // 既存のルール画面。
		QUIT, // アプリケーションの正常終了。
	};
	NextScene nextscene = NONE;

	void Init();   // 素材を読み込み、選択位置・入力・遷移要求を初期化する。
	void Update(); // マウス位置と左クリックから選択項目・遷移要求を更新する。
	void Render(); // 背景、タイトル、メニュー、操作案内を描画する。
	void Exit();   // このクラスが作った画像・フォントを解放する。
};