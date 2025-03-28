#include "TimerManager.h"

void TimerManager::Init()
{
	timer = new Timer;
	timer->Init();
}

void TimerManager::Release()
{
	timer->Release();
	delete timer;
	timer = nullptr;
}

void TimerManager::Update()
{
	if (timer)
		timer->Tick();
}

void TimerManager::Render(HDC hdc)
{
	if (timer)
	{
		wsprintf(szText, TEXT("FPS: %d"), timer->GetFPS());
		TextOut(hdc, WINSIZE_X - WINSIZE_X / 3, WINSIZE_Y / 8, szText, wcslen(szText));
	}
}

float TimerManager::GetDeltaTime()
{
	if (timer)
		return timer->GetDeltaTime();
	return 0.0f;
}
