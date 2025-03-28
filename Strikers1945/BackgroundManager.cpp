#include "BackgroundManager.h"
#include "ImageManager.h"
#include "Image.h"

void BackgroundManager::Init()
{
    image = ImageManager::GetInstance()->AddImage("UI_Background", TEXT("Image/UI/Background.bmp"), 439, 3581);
    currPosY = 2781;
}

void BackgroundManager::Release()
{
    ImageManager::GetInstance()->DeleteImage("UI_Backgorund");
    image = nullptr;
}

void BackgroundManager::Render(HDC hdc)
{
    if (image)
        image->Render(hdc,0,currPosY);
}

void BackgroundManager::Update()
{
    // TODO : update currPosY

}

int BackgroundManager::GetCurrPosY()
{
    return currPosY;
}
