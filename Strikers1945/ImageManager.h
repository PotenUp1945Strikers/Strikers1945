#pragma once
#include "Singleton.h"
#include "Image.h";
#include "config.h";
#include <map>

#define ENEMY "Image/ufo.bmp"
#define PLAYER "Image/rocket.bmp"
#define NORMAL_MISSILE "Image/bullet.bmp"

class ImageManager: public Singleton<ImageManager>
{
private:
	map<const wchar_t*, Image*> store;

public:
	void Init();
	void Release();
	Image* AddImage(const wchar_t* key, const WCHAR* filepath,
		int width, int height,
		bool isTransparent = FALSE,
		COLORREF transColor = FALSE);
	Image* AddImage(const wchar_t* key, const WCHAR* filepath,
		int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE,
		COLORREF transColor = FALSE);
	void DeleteImage(const wchar_t* key);
	Image* GetImage(const wchar_t* key);

};

