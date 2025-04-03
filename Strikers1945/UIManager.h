#pragma once
#include "config.h"
#include "Singleton.h"

class UI;
class InGameUI;
class NumberUI;
class UIManager : public Singleton<UIManager>
{
private:
	UI* intro;
	UI* pause;
	UI* player1Gameover;
	UI* player2Gameover;
	UI* ending;

	InGameUI* player1Life;
	InGameUI* player1Bomb;

	InGameUI* player2Life;
	InGameUI* player2Bomb;

	NumberUI* number1;
	NumberUI* number2;

public:
	
	void Init();
	void Release();
	void Update();
	void UpdateGameOver(int count);
	void RenderIntro(HDC hdc);
	void RenderPause(HDC hdc);
	void RenderInGame(HDC hdc);
	void RenderGameOver(HDC hdc);
	void RenderEnding(HDC hdc);
	void SetPlayer1Life(int input);
	void SetPlayer1Bomb(int input);
	void SetPlayer2Life(int input);
	void SetPlayer2Bomb(int input);

};

