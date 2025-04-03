#pragma once
#include "GameObject.h"

class Image;
class Missile : public GameObject
{
private:
	int		currFrameX;
	int		maxFrameX;
	float	frameTime;

public:
	void Init() override;
	void Init(Type type);
	void Init(FPOINT dir, float speed, Image* image, RECT size, int damage, int maxFrameX);
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
	void OnDamage(int damage) override;
	//RECT GetCollider();

	bool Shoot(FPOINT pos, FPOINT dir);
	
private:
	bool outOfWindow();
};
