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
	BackgroundManager::GetInstance()->Init();
	//UIManager::GetInstance()->Init();
	
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
	KeyManager::GetInstance()->Release();
	KeyManager::ReleaseInstance();
	/*UIManager::GetInstance()->Release();
	UIManager::ReleaseInstance();*/
	BackgroundManager::GetInstance()->Release();
	BackgroundManager::ReleaseInstance();
	EventHandler::ReleaseInstance();
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
	//UIManager::GetInstance()->RenderIntro(hdc);
}

void MainGame::RenderInGame(HDC hdc)
{
	BackgroundManager::GetInstance()->Render(hdc);
	//UIManager::GetInstance()->RenderInGame(hdc);
}

void MainGame::RenderPause(HDC hdc)
{
	BackgroundManager::GetInstance()->Render(hdc);
	//UIManager::GetInstance()->RenderPause(hdc);
}

void MainGame::RenderEnding(HDC hdc)
{
	//UIManager::GetInstance()->RenderEnding(hdc);
}

void MainGame::UpdateIntro()
{
	if (PressAnyKey())
		state = GameStates::InGame;
}

void MainGame::UpdateInGame()
{
	KeyManager* km = KeyManager::GetInstance();

	if (km->IsOnceKeyDown(PAUSE_KEY)
		|| km->IsStayKeyDown(PAUSE_KEY))
	{
		state = GameStates::Pause;
		return;
	}
	
	BackgroundManager::GetInstance()->Update();
	EventHandler::GetInstance()->Update();
}

void MainGame::UpdatePause()
{
	KeyManager* km = KeyManager::GetInstance();

	if (km->IsOnceKeyDown(PAUSE_KEY)
		|| km->IsStayKeyDown(PAUSE_KEY))
		state = GameStates::InGame;
}

void MainGame::UpdateEnding()
{
	KeyManager* km = KeyManager::GetInstance();
	
	if (km->IsOnceKeyDown(REGAME_KEY)
		|| km->IsStayKeyDown(REGAME_KEY))
		state = GameStates::Intro;
}

bool MainGame::PressAnyKey()
{
	KeyManager* km = KeyManager::GetInstance();

	for (int key = 0; key < MAX_KEY_COUNT; ++key)
	{
		if (km->IsOnceKeyDown(key)
			|| km->IsStayKeyDown(key))
			return true;
	}
	return false;
}
