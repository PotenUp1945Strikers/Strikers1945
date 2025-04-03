#pragma once
#include "config.h"
#include "GameObject.h"

struct BombInfo {
	FPOINT planePos[3];
	FPOINT dropPos[3][6];
	float miniBombDropTime;
	float currDropTime[3][6];
	int randDropFrameX[3][6];
	bool hasDropped[3][6];
	bool onEffect[3][6];
};

class Image;
class Bomb : public GameObject
{
private:


	Image* bombPlaneImage;
	Image* miniBombImage;
	Image* bombEffectImage;

	BombInfo bombInfo;

	int currDropInd;
	int currDropFrameX;
	int maxDropFrameX;

	float currTime;
	float frameDuration;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDamage() override;

	float GetBombPlanePosY();


};

