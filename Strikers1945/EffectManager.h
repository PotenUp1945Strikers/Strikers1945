#pragma once
#include "Singleton.h"
#include "config.h"
#include <map>
class GameObject;

struct Effect
{
	const wchar_t* key;
	bool active;
	GameObject* owner;
	int frameX;
	int frameY;
	float elapsedTime;
};

class EffectManager : public Singleton<EffectManager>
{
private:
	map<GameObject*, Effect> dict;
public:
	void Update();
	void Render(HDC hdc);
	void Release();
	void AddEffect(GameObject* owner);
	void OnEffect(GameObject* owner);
};