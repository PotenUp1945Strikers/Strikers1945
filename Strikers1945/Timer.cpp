#include "Timer.h"

void Timer::Init()
{
    timeScale = 0;
    timeElapsed = 0;
    currTime = 0;
    lastTime = 0;
    periodFrequency = 0;
    fpsTimeElapsed = 0;
    fpsFrameCount = 0;
    FPS = 0;
    
    isHardware = QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);
    if (isHardware)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
        timeScale = 1.0f / periodFrequency;
    }
    else
    {
        lastTime = timeGetTime();
        timeScale = 0.001f;
    }

}

void Timer::Release()
{
}

void Timer::Tick()
{
    if (isHardware)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
    }
    else
    {
        currTime = timeGetTime();
    }

    timeElapsed = (currTime - lastTime) * timeScale;
    fpsTimeElapsed += timeElapsed;
    ++fpsFrameCount;
    if (fpsTimeElapsed >= 1.0f)
    {
        FPS = fpsFrameCount;
        fpsFrameCount = 0.0f;
        fpsTimeElapsed = 0.0f;
    }

    lastTime = currTime;
}

float Timer::GetCurrTime()
{
    __int64 time = 0;

    if (isHardware)
    {
        QueryPerformanceCounter((LARGE_INTEGER*)&time);
    }
    else
    {
        time = timeGetTime();
    }

    return time * timeScale;
}
