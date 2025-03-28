#pragma once
#include "config.h"
#include "Singleton.h"
#include "Timer.h"

class TimerManager: public Singleton<TimerManager>
{
private:
	Timer* timer;
	WCHAR szText[128];

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	float GetDeltaTime();

};

