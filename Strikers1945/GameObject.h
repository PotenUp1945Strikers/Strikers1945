#pragma once
#include "config.h"

class Image;

class GameObject
{
private:
	Type type;
	bool active;
	bool render;
	FPOINT dir;
	FPOINT pos;
	float speed;
	Image* image;
	int health;

	virtual bool OutOfWindow();

public:

	virtual void Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	Type GetType();
	bool GetActive();
	bool GetRender();
	void OnDamage();



};

