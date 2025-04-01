#pragma once
#include "config.h"

class GameObject;
class Collider
{
private:
	CollisionType type;
	FPOINT pos; // 충돌체 사각형 중점
	float size;
	RECT collisionRC;
	GameObject* owner;

public:
	void Init(GameObject* owner, CollisionType type, FPOINT pos, float size);
	void Update();
	void Render(HDC hdc);
	void Release();
	
	bool IsColliding(const Collider& other);
	CollisionType GetType() { return type; }
};

