#include "MainGame.h"
#include "CommonFunction.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);
	state = GameStates::Intro;
	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("Cannot Create Back Buffer"), TEXT("Warning"), MB_OK);
	}

	ImageManager::GetInstance()->Init();

	CollisionManager::GetInstance()->Init();

	BackgroundManager::GetInstance()->Init();

	UIManager::GetInstance()->Init();

	PlayerManager::GetInstance()->Init();

	EnemyManager::GetInstance()->Init();

	EventHandler::GetInstance()->Init();
}

void MainGame::Release()
{
	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);
	
	EventHandler::ReleaseInstance();

	PlayerManager::GetInstance()->Release();
	PlayerManager::ReleaseInstance();

	EnemyManager::GetInstance()->Release();
	EnemyManager::ReleaseInstance();

	KeyManager::GetInstance()->Release();
	KeyManager::ReleaseInstance();

	UIManager::GetInstance()->Release();
	UIManager::ReleaseInstance();

	BackgroundManager::GetInstance()->Release();
	BackgroundManager::ReleaseInstance();

	CollisionManager::GetInstance()->Release();
	CollisionManager::ReleaseInstance();

	ImageManager::GetInstance()->Release();
	ImageManager::ReleaseInstance();

	EffectManager::GetInstance()->Release();
	EffectManager::ReleaseInstance();
}

void MainGame::Update()
{
	switch (state)
	{
	case GameStates::Intro:
		UpdateIntro();
		break;
	case GameStates::InGame:
		UpdateInGame();
		break;
	case GameStates::Pause:
		UpdatePause();
		break;
	case GameStates::GameOver:
		UpdateGameOver();
		break;
	case GameStates::Ending:
		UpdateEnding();
		break;
	}
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	switch (state)
	{
	case GameStates::Intro:
		RenderIntro(hBackBufferDC);
		break;
	case GameStates::InGame:
		RenderInGame(hBackBufferDC);
		break;
	case GameStates::Pause:
		RenderPause(hBackBufferDC);
		break;
	case GameStates::GameOver:
		RenderGameOver(hBackBufferDC);
		break;
	case GameStates::Ending:
		RenderEnding(hBackBufferDC);
		break;
	}

	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::RenderIntro(HDC hdc)
{
	UIManager::GetInstance()->RenderIntro(hdc);
}

void MainGame::RenderInGame(HDC hdc)
{
	BackgroundManager::GetInstance()->Render(hdc);

	PlayerManager::GetInstance()->Render(hdc);

	EnemyManager::GetInstance()->Render(hdc);

	//CollisionManager::GetInstance()->Render(hdc);

	UIManager::GetInstance()->RenderInGame(hdc);

	EffectManager::GetInstance()->Render(hdc);
}

void MainGame::RenderPause(HDC hdc)
{
	RenderInGame(hdc);
	UIManager::GetInstance()->RenderPause(hdc);
}

void MainGame::RenderGameOver(HDC hdc)
{
	RenderInGame(hdc);
	UIManager::GetInstance()->RenderGameOver(hdc);
}

void MainGame::RenderEnding(HDC hdc)
{
	UIManager::GetInstance()->RenderEnding(hdc);
}

void MainGame::UpdateIntro()
{
	if (PressAnyKey())
		state = GameStates::InGame;
}

void MainGame::UpdateInGame()
{
	KeyManager* km = KeyManager::GetInstance();

	if (EventHandler::GetInstance()->IsGameOver())
	{
		state = GameStates::GameOver;
		gameOverTime = 10;
		return;
	}
	if (EventHandler::GetInstance()->IsGameClear())
	{
		state = GameStates::Ending;
		return;
	}

	BackgroundManager::GetInstance()->Update();

	PlayerManager::GetInstance()->Update();

	EnemyManager::GetInstance()->Update();

	CollisionManager::GetInstance()->Update();

	EffectManager::GetInstance()->Update();

	if (km->IsOnceKeyDown(SUICIDE_KEY))
		return EventHandler::GetInstance()->GameOver();
	if (km->IsOnceKeyDown(CLEAR_KEY))
		return EventHandler::GetInstance()->GameClear();
	if (km->IsOnceKeyDown(PAUSE_KEY))
		state = GameStates::Pause;
}

void MainGame::UpdatePause()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(PAUSE_KEY))
		state = GameStates::InGame;
}

void MainGame::UpdateGameOver()
{
	if (gameOverTime < 0)		
		return ReGame();
	if (PressAnyKey())
	{
		EventHandler::GetInstance()->Init();
		PlayerManager::GetInstance()->Init();
		state = GameStates::InGame;
		return;
	}
	
	gameOverTime -= TimerManager::GetInstance()->GetDeltaTime();
	UIManager::GetInstance()->UpdateGameOver(gameOverTime);
}

void MainGame::UpdateEnding()
{
	if (KeyManager::GetInstance()->IsOnceKeyDown(REGAME_KEY))
		ReGame();
}

bool MainGame::PressAnyKey(void)
{
	KeyManager* km = KeyManager::GetInstance();

	for (int key = 0; key < MAX_KEY_COUNT; ++key)
	{
		if (km->IsOnceKeyDown(key))
			return true;
	}
	return false;
}

void MainGame::ReGame(void)
{
	PlayerManager::GetInstance()->Init();
	BackgroundManager::GetInstance()->Init();
	EnemyManager::GetInstance()->Init();
	EventHandler::GetInstance()->Init();
	state = GameStates::Intro;
}
