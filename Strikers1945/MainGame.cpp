#include "MainGame.h"
#include "CommonFunction.h"

void MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	if (FAILED(backBuffer->Init(WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd, 
			TEXT("����� ���� ����"), TEXT("���"), MB_OK);
	}
	backGround = new Image();
	if (FAILED(backGround->Init(TEXT("Image/BackGround.bmp"), WINSIZE_X, WINSIZE_Y)))
	{
		MessageBox(g_hWnd,
			TEXT("Image/backGround.bmp ���� ����"), TEXT("���"), MB_OK);
	}
}

void MainGame::Release()
{
	if (backGround)
	{
		backGround->Release();
		delete backGround;
		backGround = nullptr;
	}

	if (backBuffer)
	{
		backBuffer->Release();
		delete backBuffer;
		backBuffer = nullptr;
	}

	ReleaseDC(g_hWnd, hdc);
	KeyManager::GetInstance()->ReleaseInstance();
	KeyManager::ReleaseInstance();
}

void MainGame::Update()
{
	
}

void MainGame::Render()
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	backBuffer->Render(hdc);
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
