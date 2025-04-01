#pragma once
#include "GameObject.h"

class Missile : public GameObject
{
private:
	RECT size;

public:
	void Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	RECT GetCollider();
	
private:
	bool outOfWindow();
};

