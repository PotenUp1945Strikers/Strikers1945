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
	UI* gameOver;
	UI* ending;
	InGameUI* life;
	InGameUI* bomb;
	NumberUI* number1;

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
	void SetLife(int input);
	void SetBomb(int input);

};

