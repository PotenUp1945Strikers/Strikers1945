#pragma once
#include "config.h"
#include "Singleton.h"
#include "TimerManager.h"

class Image;
class ImageManager;
class BackgroundManager : public Singleton<BackgroundManager>
{
private:
	Image*	image;
	float	tileY[2];
	float	screenY[2];
	float	speed;
	float	currPosY;

public:

	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();
	float GetCurrPosY();
};

