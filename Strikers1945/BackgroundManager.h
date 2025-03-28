#pragma once
#include "config.h"
class Image;
class ImageManager;
class BackgroundManager : public Singleton<BackgroundManager>
{
private:
	Image* image;
	int currPosY;

public:

	void Init();
	void Release();
	void Render(HDC hdc);
	void Update();
	int GetCurrPosY();

};

