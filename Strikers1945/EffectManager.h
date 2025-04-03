#pragma once
#include "Singleton.h"
#include "config.h"
#include <map>
class GameObject;

struct Effect
{
	bool active;
	FPOINT pos;
	int frameX;
	int frameY;
	float elapsedTime;
};

class EffectManager : public Singleton<EffectManager>
{
private:
	//map<const wchar_t*, Effect> dict;
	map<const wchar_t*, vector<Effect>> dict;
	void FillDict();
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
	void OnEffect(const wchar_t* key, FPOINT pos);
};