#include "UIManager.h"
#include "Image.h"
#include "ImageManager.h"
#include "UI.h"
#include "InGameUI.h"
#include "NumberUI.h"

void UIManager::Init()
{
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

	if (!player1Gameover)
	{
		player1Gameover = new UI;
		player1Gameover->Init();
		player1Gameover->SetImage(TEXT(GAMEOVER_PATH));
	}
	if (!player2Gameover)
	{
		player2Gameover = new UI;
		player2Gameover->Init();
		player2Gameover->SetImage(TEXT(GAMEOVER_PATH));
	}
	
	if (!ending)
	{
		ending = new UI;
		ending->Init();
		ending->SetImage(TEXT(ENDING_PATH));
	}
	
	if (!player1Life)
	{
		player1Life = new InGameUI;
		player1Life->SetPlayerNum(PlayerNum::PLAYER1);
		player1Life->Init({ 36, 50 });
		player1Life->SetImage(TEXT(LIFE_COUNT_PATH));
		player1Life->Setinterval(42);
	}
	player1Life->SetCount(3);

	if (!player1Bomb)
	{
		player1Bomb = new InGameUI;
		player1Bomb->SetPlayerNum(PlayerNum::PLAYER1);
		player1Bomb->Init({ 38, WINSIZE_Y - 50 });
		player1Bomb->SetImage(TEXT(BOMB_COUNT_PATH));
		player1Bomb->Setinterval(38);
	}
	player1Bomb->SetCount(2);

	if (!number1)
	{
		number1 = new NumberUI;
		number1->Init({ 390, 418 });
		number1->SetImage(TEXT(NUMBER_SET1_PATH));
		number1->SetInterval(38);
	}
	number1->SetNumber(10);


	if (!player2Life)
	{
		player2Life = new InGameUI;
		player2Life->SetPlayerNum(PlayerNum::PLAYER2);
		player2Life->Init({ WINSIZE_X - 36, 50 });
		player2Life->SetImage(TEXT(LIFE_COUNT_PATH));
		player2Life->Setinterval(42);
	}		  
	player2Life->SetCount(3);

	if (!player2Bomb)
	{
		player2Bomb = new InGameUI;
		player2Bomb->SetPlayerNum(PlayerNum::PLAYER2);
		player2Bomb->Init({ WINSIZE_X - 38, WINSIZE_Y - 50 });
		player2Bomb->SetImage(TEXT(BOMB_COUNT_PATH));
		player2Bomb->Setinterval(38);
	}
	player2Bomb->SetCount(2);

	if (!number2)
	{
		number2 = new NumberUI;
		number2->Init({ 390, 418 });
		number2->SetImage(TEXT(NUMBER_SET1_PATH));
		number2->SetInterval(38);
	}
	number2->SetNumber(10);
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
	if (player1Gameover)
	{
		delete player1Gameover;
		player1Gameover = nullptr;
	}
	if (ending)
	{
		delete ending;
		ending = nullptr;
	}
	if (player1Life)
	{
		delete player1Life;
		player1Life = nullptr;
	}
	if (player1Bomb)
	{
		delete player1Bomb;
		player1Bomb = nullptr;
	}
	if (number1)
	{
		delete number1;
		number1 = nullptr;
	}
}

void UIManager::Update()
{
	if (player1Life)
		player1Life->Update();
	if (player1Bomb)
		player1Bomb->Update();
	if (player2Life)
		player2Life->Update();
	if (player2Bomb)
		player2Bomb->Update();
}

void UIManager::UpdateGameOver(int count)
{
	if (number1)
		number1->SetNumber(count);
	if (number2)
		number2->SetNumber(count);
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
	if (player1Life)
		player1Life->Render(hdc);
	if (player1Bomb)
		player1Bomb->Render(hdc);
	if (player2Life)
		player2Life->Render(hdc);
	if (player2Bomb)
		player2Bomb->Render(hdc);
}

void UIManager::RenderGameOver(HDC hdc)
{
	if (player1Gameover)
		player1Gameover->Render(hdc);
	if (number1)
		number1->Render(hdc);

	if (player2Gameover)
		player2Gameover->Render(hdc);
	if (number2)
		number2->Render(hdc);
}

void UIManager::RenderEnding(HDC hdc)
{
	if (ending)
		ending->Render(hdc);
}

void UIManager::SetPlayer1Life(int input)
{
	if(player1Life)
		player1Life->SetCount(input);
}

void UIManager::SetPlayer1Bomb(int input)
{
	if (player1Bomb)
	{
		if (input <= 0) input = 0;
		player1Bomb->SetCount(input);
	}
}

void UIManager::SetPlayer2Life(int input)
{
	if (player2Life)
		player2Life->SetCount(input);
}

void UIManager::SetPlayer2Bomb(int input)
{
	if (player2Bomb)
	{
		if (input <= 0) input = 0;
		player2Bomb->SetCount(input);
	}
}
