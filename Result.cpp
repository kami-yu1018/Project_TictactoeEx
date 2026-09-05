//	ƒGƒ“ƒfƒBƒ“ƒO‰æ–ÊiŒ‹‰Ê”­•\j

#include"Result.h"
#include"main.h"

void Result::Init()
{
	//	”wŒi‰æ‘œ‚Ì“Ç‚İ‚İ
	backgroundImage = LoadGraph("data/background.png");	//	”wŒi
	resultImage[0] = LoadGraph("data/win_text.png");	//	Ÿ‚¿
	resultImage[1] = LoadGraph("data/lose_text.png");	//	•‰‚¯
}

void Result::Update()
{

}

void Result::Render(int playresult)
{
	//	”wŒi‰æ‘œ‚Ì•`‰æ
	DrawGraph(0, 0, backgroundImage, TRUE);
	if(playresult==1)	//	Ÿ‚¿‚Ì
	{ 
		DrawGraph(150, 100, resultImage[0], TRUE);
	}
	else if (playresult == 2)	//	•‰‚¯‚Ì
	{
		DrawGraph(150, 100, resultImage[1], TRUE);
	}
}

void Result::Exit()
{
	//	”wŒi‰æ‘œ‚Ì‰ğ•ú
	DeleteGraph(backgroundImage);
}