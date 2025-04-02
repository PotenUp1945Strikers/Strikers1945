#pragma once
#include "Plane.h"
#include "GameObject.h"
#include "config.h"

class Boss: public GameObject
{
private:
	Plane* left;
	Plane* right;
	Plane* Center;

public:
	void Init(void);
	void Update(void);
	void Release(void);
	void Render(HDC hdc);
};

