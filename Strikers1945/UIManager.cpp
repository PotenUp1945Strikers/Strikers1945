#include "UIManager.h"
#include "Image.h"
#include "ImageManager.h"


void UIManager::Init()
{
	// TODO : Init

	intro->Init();
	pause->Init();
	ending->Init();
	life->Init();
	bomb->Init();

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
	if (GameStates::InGame)
	{
		if (life)
			life->Render(hdc);
		if (bomb)
			bomb->Render(hdc);
	}
}

void UIManager::Update()
{
	switch (GameManager::GetInstance()->GetCurrState())
	{
		case GameStates::Intro:
			
			if(intro)
				intro->Update(hdc);
			break;
		case GameStates::InGame:
			
			if(life)
				life->Update(hdc);
			if(bomb)
				bomb->Update(hdc);
			break;
		case GameStates::Pause:
		
			if(pause)
				pause->Update(hdc);
			break;
		case GameStates::Ending:
			if(ending)
				ending->Update(hdc);
			break;
	}
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

void UIManager::RenderEnding(HDC hdc)
{
	if (ending)
		ending->Render(hdc);
}

void UIManager::SetLife(int input)
{
	if(life)
		life->SetLife(input);
}

void UIManager::setBomb(int input)
{
	if(life)
		life->SetBomb(input);
}
