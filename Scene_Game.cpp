#include "Scene_Game.h"

//　初期化処理
void Scene_Game::Init()
{
	player_turn = true;
}

//　勝利判定をする関数
int Scene_Game::CheckWin()
{
	//　勝利に必要な記号の数
	int win_count = 3;

	//　晩面が3×3の時
	if (board_size == 3)
	{
		//　勝利に必要な記号の数は3
		win_count = 3;
	}
	//　晩面が4×4の時
	else if (board_size == 5)
	{
		//　4
		win_count = 4;
	}
	//　晩面が5×5の時
	else
	{
		//　5
		win_count = 5;
	}


}

//　更新処理
void Scene_Game::Update()
{
	//　マウスカーソルの座標を取得
	GetMousePoint(&mouse_pos_x, &mouse_pos_y);

	//　マウスの入力状態を取得
	mouse_input = GetMouseInput();

	//　盤面のサイズを制限
	if (board_size >= 7)
	{
		//　一番大きいときは 7×7
		board_size = 7;
	}

	//　盤面のサイズを更新
	//　盤面が埋まったら
	if (count >= 9 && count < 25)
	{
		//　盤面のサイズを大きくする
		board_size = 5;
	}
	//　また盤面が埋まったら
	else if (count >= 25 && count < 49)
	{
		//　さらに大きくする
		board_size = 7;
	}

	//　左クリックが押されたら
	if (mouse_input & MOUSE_INPUT_LEFT && key_state == false)
	{
		//　盤面のマスをループして、マウスカーソルがどのマスにあるかを判定する
		for (int j = 0; j < board_size; j++)
		{
			for (int i = 0; i < board_size; i++)
			{
				//　盤面のセルのサイズを計算
				int cell_size = 700 / board_size;

				int x1 = 50 + cell_size * i;
				int y1 = 100 + cell_size * j;
				int x2 = x1 + cell_size;
				int y2 = y1 + cell_size;

				//マウスがこのマスの中にあるか
				if (mouse_pos_x >= x1 && mouse_pos_x < x2 &&
					mouse_pos_y >= y1 && mouse_pos_y < y2)
				{
					//　空いているマスなら
					if (draw_board[j][i] == 0)
					{
						//　○のターン
						if (player_turn == true)
						{
							draw_board[j][i] = 1;
						}
						//　×のターン
						else
						{
							draw_board[j][i] = 2;
						}

						//　置いた数を増やす
						count++;

						//　プレイヤー交代
						player_turn = !player_turn;
					}
				}
			}
		}
	}

	//　プレイヤーのターンを交互に切り替える
	if (count % 2 == 0)
	{
		player_turn = true;
	}
	else
	{
		player_turn = false;
	}

	//　マウスの長押し入力の防止
	if (mouse_input == true)
	{
		key_state = true;
	}
	else
	{
		key_state = false;
	}
}

//　描画処理
void Scene_Game::Render()
{
	//　盤面の描画
	for (int j = 0; j < board_size; ++j)
	{
		for (int i = 0; i < board_size; ++i)
		{
			int x1 = 50 + (700 / board_size) * (i);
			int y1 = 100 + (700 / board_size) * (j);
			int x2 = x1 + (700 / board_size);
			int y2 = y1 + (700 / board_size);
			DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);

			//　盤面のセルのサイズを計算
			int cell_size = 700 / board_size;
			int center_x = 50 + cell_size * i + cell_size / 2;
			int center_y = 100 + cell_size * j + cell_size / 2;

			//　先手の人の番で盤面に記号が置かれている状態なら
			if(draw_board[j][i] == 1)
			{
				//　赤い丸〇を描画
				DrawCircle(center_x, center_y, cell_size / 3, GetColor(255, 0, 0), FALSE);
			}
			else if (draw_board[j][i] == 2)
			{
				int size = cell_size / 3;
				//　青い×を描画
				DrawLine(center_x - size, center_y - size, center_x + size, center_y + size, GetColor(0, 0, 255));
				DrawLine(center_x + size, center_y - size, center_x - size, center_y + size, GetColor(0, 0, 255));
			}
		}
	}

	//　プレイヤーのターンを画面中央上に表示
	if(player_turn == true)
	{
		DrawFormatString(340, 50, GetColor(255, 255, 255), "〇の人のターンです");
	}
	else
	{
		DrawFormatString(340, 50, GetColor(255, 255, 255), "×の人のターンです");
	}
}

//　終了処理
void Scene_Game::Exit()
{

}