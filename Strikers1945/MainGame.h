#pragma once
#include "Image.h"
#include "KeyManager.h"
#include "UIManager.h"
#include "BackgroundManager.h"
#include "EventHandler.h"
#include "PlayerManager.h"
#include "EnemyManager.h"
#include "EffectManager.h"

class MainGame
{
private:
	HDC			hdc;
	GameStates	state;
	float		gameOverTime;
	Image*		backBuffer;

	void RenderIntro(HDC hdc);
	void RenderInGame(HDC hdc);
	void RenderPause(HDC hdc);
	void RenderGameOver(HDC hdc);
	void RenderEnding(HDC hdc);

	void UpdateIntro();
	void UpdateInGame();
	void UpdatePause();
	void UpdateGameOver();
	void UpdateEnding();

	bool PressAnyKey();
	void ReGame(void);

public:
	void Init();	
	void Release();	
	void Update();	
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

