#include "config.h"
#include "MainGame.h"
#include "TimerManager.h"

HINSTANCE g_hInstance;
HWND g_hWnd;
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("Strikers 1945");
MainGame g_mainGame;

RECT GetRect(int left, int top, int width, int height);
RECT GetRectAtCenter(int x, int y, int width, int height);

void RenderStar(HDC hdc, int posX, int posY);
void RenderRect(HDC hdc, int x, int y, int width, int height);
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderEllipse(HDC hdc, int x, int y, int width, int height);
void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height);

bool PointInRect(FPOINT ptMouse, RECT rc);
bool RectInRect(RECT rc1, RECT rc2);
void UpdateRect(RECT& rc, FPOINT pt);


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
	LPSTR lpszCmdParam, int nCmdShow)
{
	srand(time(NULL));
	g_hInstance = hInstance;

	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.cbClsExtra = 2068;
	wndClass.cbWndExtra = 2068;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW);
	wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClassName;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHIELD));

	RegisterClassEx(&wndClass);

	RECT rcWindowSize = { 0, 0, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRect(&rcWindowSize, WS_OVERLAPPEDWINDOW, FALSE);
	int width = rcWindowSize.right - rcWindowSize.left;
	int height = rcWindowSize.bottom - rcWindowSize.top;

	g_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_lpszClassName, g_lpszClassName,
		WS_OVERLAPPEDWINDOW, 50, 50, width, height,
		NULL, NULL, g_hInstance, NULL);

	ShowWindow(g_hWnd, nCmdShow);

	TimerManager::GetInstance()->Init();
	g_mainGame.Init();

	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
				break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimerManager::GetInstance()->Update();
			g_mainGame.Update();
			g_mainGame.Render();
		}
	}

	TimerManager::GetInstance()->Release();
	TimerManager::ReleaseInstance();
	g_mainGame.Release();

	return message.wParam;
}

LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
