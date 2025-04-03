#pragma once
#include "Singleton.h"
#include "Plane.h"
#include "config.h"
#include "KeyManager.h"
#include "CollisionManager.h"
#include "EventHandler.h"
#include "UIManager.h"
#include <map>
#include <vector>

class PlayerManager: public Singleton<PlayerManager>
{
private:
	static map<const wchar_t*, vector<Task>*> dict;

	Plane*	player1;
	int		player1Life;
	int		player1Bomb;
	Plane*	player2;
	int		player2Life;
	int		player2Bomb;

	void FillDict(void);
	void LaunchBomb(PlayerNum playerNum);

public:
	void Init(void);
	void Update(void);
	void Render(HDC hdc);
	void Release(void);
	
	void LaunchBombEnd();

	int GetPlayer1bomb();
	bool ReducePlayer1Bomb();
	bool InCreasePlayer1Bomb();
	

	int GetPlayer2bomb();
	bool ReducePlayer2Bomb();
	bool InCreasePlayer2Bomb();

	
	bool Revive(void);
};

