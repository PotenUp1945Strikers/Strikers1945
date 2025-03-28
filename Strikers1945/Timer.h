#pragma once
#include "config.h"

class Timer
{
private:
	bool			isHardware;
	float			timeScale;
	float			timeElapsed;
	__int64			currTime;
	__int64			lastTime;
	__int64			periodFrequency;
	float			fpsTimeElapsed;
	unsigned long	fpsFrameCount;
	unsigned long	FPS;

public:
	void Init();
	void Release();
	void Tick();
	float GetCurrTime();

	inline unsigned long GetFPS() { return FPS; }
	inline float GetDeltaTime() { return timeElapsed; }
};

