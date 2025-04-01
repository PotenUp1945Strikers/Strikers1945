#pragma once
#include "config.h"

class Image;
class UI
{
protected:
	Image* image;
	int currFrameX;
	int currFrameY;
	FPOINT renderPos;
	float elapsedTime;

public:
	void Init();
	void Init(FPOINT renderPos);
	void Release();
	void Update();
	virtual void Render(HDC hdc);

	void SetImage(const wchar_t* key);

	UI() {};
	virtual ~UI() {};
};