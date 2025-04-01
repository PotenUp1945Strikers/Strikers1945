#pragma once
#include "config.h"

class GameObject;
class Collider
{
private:
	Type type;
	FPOINT pos; // �浹ü �簢�� ����
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

