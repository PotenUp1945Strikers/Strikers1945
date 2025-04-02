#pragma once
#include "BackgroundManager.h"
#include "config.h"

class EventHandler: public Singleton<EventHandler>
{
private:
	bool gameOver;
	bool gameClear;

public:
	void Init();
	bool IsGameOver();
	bool IsGameClear();
	void GameOver();
	void GameClear();
};

