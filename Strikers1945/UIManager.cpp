#include "UIManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "UI.h"
#include "InGameUI.h"
#include "NumberUI.h"

void UIManager::Init()
{
	// TODO : Init
	if (!intro)
	{
		intro = new UI;
		intro->Init();
		intro->SetImage(TEXT(OPENING_PATH));
	}

	if (!pause)
	{
		pause = new UI;
		pause->Init();
		pause->SetImage(TEXT(PAUSE_PATH));
	}

	if (!gameOver)
	{
		gameOver = new UI;
		gameOver->Init();
		gameOver->SetImage(TEXT(GAMEOVER_PATH));
	}
	
	if (!ending)
	{
		ending = new UI;
		ending->Init();
		ending->SetImage(TEXT(ENDING_PATH));
	}
	
	if (!life)
	{
		life = new InGameUI;
		life->SetImage(TEXT(LIFE_COUNT_PATH));
		life->Init({ 50 - 8 , 50 });
		life->Setinterval(20);
		life->SetCount(3);
	}

	if (!bomb)
	{
		bomb = new InGameUI;
		bomb->Init({ 38, WINSIZE_Y - 50 });
		bomb->SetImage(TEXT(BOMB_COUNT_PATH));
		bomb->Setinterval(38);
		bomb->SetCount(2);
	}


	if (!number1)
	{
		number1 = new NumberUI;
		number1->Init({ 390, 418 });
		number1->SetImage(TEXT(NUMBER_SET1_PATH));
		number1->SetInterval(38);
		number1->SetNumber(10);
	}
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
	if (gameOver)
	{
		delete gameOver;
		gameOver = nullptr;
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
	if (bomb)
	{
		delete bomb;
		bomb = nullptr;
	}
	if (number1)
	{
		delete number1;
		number1 = nullptr;
	}
}

void UIManager::Update()
{
	if (life)
		life->Update();
	if (bomb)
		bomb->Update();
}

void UIManager::UpdateGameOver(int count)
{
	if (number1)
		number1->SetNumber(count);
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

void UIManager::RenderGameOver(HDC hdc)
{
	if (gameOver)
		gameOver->Render(hdc);
	if (number1)
		number1->Render(hdc);
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
	if (bomb)
	{
		if (input <= 0) input = 0;
		bomb->SetCount(input);
	}
}
