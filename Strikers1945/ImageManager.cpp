#include "ImageManager.h"

void ImageManager::Init()
{
    AddImage(TEXT(BACKGROUND_PATH), TEXT(BACKGROUND_PATH), WINSIZE_X, BACKGROUND_SIZE);

    AddImage(TEXT(OPENING_PATH), TEXT(OPENING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PAUSE_PATH), TEXT(PAUSE_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(GAMEOVER_PATH), TEXT(GAMEOVER_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ENDING_PATH), TEXT(ENDING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(LIFE_COUNT_PATH), TEXT(LIFE_COUNT_PATH), 27, 35, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_COUNT_PATH), TEXT(BOMB_COUNT_PATH), 23, 32, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NUMBER_SET1_PATH), TEXT(NUMBER_SET1_PATH), 38, 380, 1, 10, true, RGB(255, 0, 255));

    AddImage(TEXT(PLAYER_PATH), TEXT(PLAYER_PATH), 32, 47, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY1_PATH), TEXT(ENEMY1_PATH), 39, 32, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NORMAL_BULLET_PATH), TEXT(NORMAL_BULLET_PATH), 33, 49, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(HIT_EFFECT_PATH), TEXT(HIT_EFFECT_PATH), 120, 40, 3, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(TARGETTING_BULLET_PATH), TEXT(TARGETTING_BULLET_PATH), 12, 12, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(AROUND_BULLET_PATH), TEXT(AROUND_BULLET_PATH), 25, 25, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_EFFECT_PATH), TEXT(BOMB_EFFECT_PATH), 512, 512, 4, 5, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT1_PATH), TEXT(EFFECT1_PATH), 512, 1536, 2, 6, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT2_PATH), TEXT(EFFECT2_PATH), 576, 48, 12, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT3_PATH), TEXT(EFFECT3_PATH), 512, 128, 8, 2, true, RGB(255, 0, 255));
    
}

void ImageManager::Release()
{
    for (auto& iter : store)
        iter.second->Release();

    store.clear();
}

Image* ImageManager::AddImage(const wchar_t* key, const WCHAR* filepath,
    int width, int height, bool isTransparent, COLORREF transColor)
{
    if (store.find(key) != store.end())
        DeleteImage(key);

    Image* image = new Image;

    if (FAILED(image->Init(filepath, width, height, isTransparent, transColor)))
    {
        image->Release();
        delete image;
        image = nullptr;
    }
    else
    {
        store.insert(make_pair(key, image));
    }
    return image;
}

Image* ImageManager::AddImage(const wchar_t* key, const WCHAR* filepath,
    int width, int height, int maxFrameX, int maxFrameY, bool isTransparent, COLORREF transColor)
{
    if (store.find(key) != store.end())
        DeleteImage(key);

    Image* image = new Image;

    if (FAILED(image->Init(filepath, width, height, maxFrameX, maxFrameY, isTransparent, transColor)))
    {
        image->Release();
        delete image;
        image = nullptr;
    }
    else
    {
        store.insert(make_pair(key, image));
    }
    return image;
}

void ImageManager::DeleteImage(const wchar_t* key)
{
    auto iter = store.find(key);

    if (iter == store.end())
        return;

    Image* image = store[key];
    image->Release();
    delete image;

    store.erase(iter);
}

Image* ImageManager::GetImage(const wchar_t* key)
{
    return store.find(key) == store.end() ? nullptr : store[key];
}
