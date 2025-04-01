#pragma once
#include "config.h"

class GameObject;
class Collider
{
private:
	Type type;
	FPOINT pos; // 충돌체 사각형 중점
	float size;
	RECT collisionRC;
	GameObject* owner;

public:
	void Init(GameObject* owner, Type type, FPOINT pos, float size);
	void Update();
	void Render(HDC hdc);
	void Release();
	
	bool IsColliding(const Collider& other);
	Type GetType() { return type; }
};

