#pragma once
#include "config.h"

class UI;
class InGameUI;
class UIManager : public Singleton<UIManager>
{
private:
	UI* intro;
	UI* pause;
	UI* Ending;
	InGameUI* life;
	InGameUI* bomb;

public:
	
	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();
	void RenderIntro(HDC hdc);
	void RenderPause(HDC hdc);
	void RenderEnding(HDC hdc);
	void SetLife(int input);
	void setBomb(int input);

};

