#pragma once
#include "config.h"

class Image;
class UI
{
protected:
	const wchar_t* key;
	Image* image;
	int currFrameX;
	int currFrameY;
	FPOINT renderPos;
	float	elapsedTime;

public:
	void Init();
	void Release();
	void Update();
	virtual void Render(HDC hdc);


	void SetImage(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY);

	UI() {};
	virtual ~UI() {};
};