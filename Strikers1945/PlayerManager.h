#pragma once
#include "Singleton.h"
#include "Plane.h"
#include "config.h"
#include "KeyManager.h"
#include "CollisionManager.h"

class PlayerManager: public Singleton<PlayerManager>
{
private:
	Plane*	player1;
	int		player1Life;
	int		player1Bomb;
	Plane*	player2;
	int		player2Life;
	int		player2Bomb;

public:
	void Init(void);
	void Update(void);
	void Render(HDC hdc);
	void Release(void);
	void LaunchBomb(void);
};

