#pragma once
#include "config.h"
#include "GameObject.h"

//struct BombInfo {
//	float currDropTime[3][6];
//	FPOINT dropPos[3][6];
//	bool hasDropped[3][6];
//	bool isExploding[3][6];
//
//};

class Image;
class Bomb : public GameObject
{
private:


	Image* bombPlaneImage;
	Image* miniBombImage;
	Image* bombEffectImage;

	FPOINT planePos[3];


	FPOINT dropPos[3][6];
	float miniBombDropTime;	
	float currDropTime[3][6];
	int randDropFrameX[3][6];
	bool hasDropped[3][6];

	int currDropInd;
	int currDropFrameX;

	int maxDropFrameX;
	float currTime;

public:
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void OnDamage() override;



};

