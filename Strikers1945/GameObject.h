#pragma once
#include "config.h"

class Image;

class GameObject
{
protected:
	Type type;
	bool active;
	bool render;
	FPOINT dir;
	FPOINT pos;
	RECT size;
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
	void SetType(Type type);
	void SetPos(FPOINT pos);
	FPOINT GetPos();
	bool GetActive();
	bool GetRender();
	void SetActive(bool active);
	void SetRender(bool render);
	RECT GetCollider();
	virtual void OnDamage() = 0;



};

