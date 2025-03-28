#include "BackgroundManager.h"
#include "ImageManager.h"
#include "Image.h"

void BackgroundManager::Init()
{
    image = ImageManager::GetInstance()->AddImage(TEXT(BACKGROUND_PATH), TEXT(BACKGROUND_PATH), 600, 4882);
    currPosY = 4082;
}

void BackgroundManager::Release()
{
    ImageManager::GetInstance()->DeleteImage(TEXT(BACKGROUND_PATH));
    image = nullptr;
}

void BackgroundManager::Render(HDC hdc)
{
    if (image)
        image->Render(hdc, currPosY);
}

void BackgroundManager::Update()
{
    deltaTime += TimerManager::GetInstance()->GetDeltaTime();
    if (deltaTime > SCROLL_TIME)
    {
        if (currPosY > 0)
            --currPosY;
        deltaTime = 0.0f;
    }


}

int BackgroundManager::GetCurrPosY()
{
    return currPosY;
}
