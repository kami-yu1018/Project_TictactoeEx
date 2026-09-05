#include "Scene_Rule.h"

Scene_Rule::Scene_Rule() 
{
	ruleImage = -1; // ƒ‹[ƒ‹‰æ‘œ‚Ìƒnƒ“ƒhƒ‹‚ğ‰Šú‰»
}

void Scene_Rule::Init()
{
	//	‰æ‘œ“Ç‚İ‚İ
	ruleImage = LoadGraph("data/Rule_image.png");
}

void Scene_Rule::Update()
{

}

void Scene_Rule::Render()
{
	DrawGraph(0, 0, ruleImage, TRUE);
}

void Scene_Rule::Exit()
{
	DeleteGraph(ruleImage);
}

bool Scene_Rule::Scene_back_flag()
{

}