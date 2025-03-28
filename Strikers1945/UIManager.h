#pragma once
#include "config.h"
#include "Singleton.h"

class UI;
class InGameUI;
class UIManager : public Singleton<UIManager>
{
private:
	UI* intro;
	UI* pause;
	UI* ending;
	InGameUI* life;
	InGameUI* bomb;

public:
	
	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();
	void RenderIntro(HDC hdc);
	void RenderPause(HDC hdc);
	void RenderInGame(HDC hdc);
	void RenderEnding(HDC hdc);
	void SetLife(int input);
	void SetBomb(int input);

};

