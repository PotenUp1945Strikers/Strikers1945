#pragma once
#include "config.h"
#include "GameObject.h"
class HoverItem : public GameObject
{
private:

	int currFrameX;
	int maxFrameX;
	int itemFrameTime;
	float currTime;
	float frameDuration;

public:
	virtual void Init() override;
			void Init(Type type, const wchar_t* key, FPOINT onDamagePos);
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDamage(int damage) override;

};

