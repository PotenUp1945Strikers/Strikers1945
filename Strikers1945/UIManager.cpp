#include "UIManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "UI.h"
#include "InGameUI.h"

void UIManager::Init()
{
	// TODO : Init

	intro->Init();
	intro->SetImage(TEXT("Image/UI/UI_Intro.bmp"), 0, 0, 0, 0);
	
	pause->Init();
	pause->SetImage(TEXT("Image/UI/UI_Pause.bmp"), 0, 0, 0, 0);
	
	ending->Init();
	ending->SetImage(TEXT("Image/UI/UI_Ending.bmp"), 0, 0, 0, 0);
	
	life->Init();
	life->SetImage(TEXT("Image/UI/UI_Life.bmp"),0,0,0,0);

	bomb->Init();
	bomb->SetImage(TEXT("Image/UI/UI_Bomb.bmp"), 0, 0, 0, 0);


}

void UIManager::Release()
{
	if (intro)
	{
		delete intro;
		intro = nullptr;
	}
	if (pause)
	{
		delete pause;
		pause = nullptr;
	}
	if (ending)
	{
		delete ending;
		ending = nullptr;
	}
	if (life)
	{
		delete life;
		life = nullptr;
	}
}

void UIManager::Render(HDC hdc)
{
		
	
}

void UIManager::Update()
{

	if (intro)
		intro->Update();
	if (life)
		life->Update();
	if (bomb)
		bomb->Update();
	if (pause)
		pause->Update();
	if (ending)
		ending->Update();
}


void UIManager::RenderIntro(HDC hdc)
{
	if (intro)
		intro->Render(hdc);
}

void UIManager::RenderPause(HDC hdc)
{
	if (pause)
		pause->Render(hdc);
}

void UIManager::RenderInGame(HDC hdc)
{
	if (life)
		life->Render(hdc);
	if (bomb)
		bomb->Render(hdc);
}

void UIManager::RenderEnding(HDC hdc)
{
	if (ending)
		ending->Render(hdc);
}

void UIManager::SetLife(int input)
{
	if(life)
		life->SetCount(input);
}

void UIManager::SetBomb(int input)
{
	if(life)
		life->SetCount(input);
}
