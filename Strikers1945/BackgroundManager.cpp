#include "BackgroundManager.h"
#include "ImageManager.h"
#include "Image.h"

void BackgroundManager::Init()
{
    if (!image)
        image = ImageManager::GetInstance()->GetImage(TEXT(BACKGROUND_PATH));
    tileY[0] = BACKGROUND_SIZE - WINSIZE_Y;
    tileY[1] = BACKGROUND_SIZE;
    screenY[0] = 0;
    screenY[1] = WINSIZE_Y;
    currPosY = 0;
    speed = BACKGROUND_SPEED;
}

void BackgroundManager::Release()
{
    image = nullptr;
}

void BackgroundManager::Render(HDC hdc)
{
    if (image)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (screenY[i] < WINSIZE_Y)
                image->RenderBackground(hdc, screenY[i], tileY[i]);
        }
    }
}

void BackgroundManager::Update()
{
    float velocity = speed * TimerManager::GetInstance()->GetDeltaTime();
    currPosY += velocity;

    for (int i = 0; i < 2; ++i)
    {
        if (screenY[i] < WINSIZE_Y)
        {
            if (tileY[i] <= 0)
            {
                screenY[i] += velocity;
                if (screenY[i] >= WINSIZE_Y)
                    tileY[i] = BACKGROUND_SIZE;
            }
            else
            {
                tileY[i] -= velocity;
                if (tileY[i] <= 0)
                    screenY[(i + 1) % 2] = 0;
            }
        }
    }
}

int BackgroundManager::GetCurrPosY()
{
    return currPosY;
}
