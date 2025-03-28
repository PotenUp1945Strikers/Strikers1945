#pragma once
#include "config.h"
#include "Singleton.h"
#include "TimerManager.h"

class Image;
class ImageManager;
class BackgroundManager : public Singleton<BackgroundManager>
{
private:
	Image* image;
	int currPosY;
	float deltaTime;

public:

	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();
	int GetCurrPosY();

};

