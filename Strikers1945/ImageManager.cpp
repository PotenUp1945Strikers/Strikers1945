#include "ImageManager.h"

void ImageManager::Init()
{
    AddImage(TEXT(BACKGROUND_PATH), TEXT(BACKGROUND_PATH), WINSIZE_X, BACKGROUND_SIZE);

    AddImage(TEXT(OPENING_PATH), TEXT(OPENING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PAUSE_PATH), TEXT(PAUSE_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(GAMEOVER_PATH), TEXT(GAMEOVER_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ENDING_PATH), TEXT(ENDING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(LIFE_COUNT_PATH), TEXT(LIFE_COUNT_PATH), 16, 21, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_COUNT_PATH), TEXT(BOMB_COUNT_PATH), 23, 32, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NUMBER_SET1_PATH), TEXT(NUMBER_SET1_PATH), 38, 380, 1, 10, true, RGB(255, 0, 255));

    AddImage(TEXT(PLAYER_PATH), TEXT(PLAYER_PATH), 352, 256, 11, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(TANK_PATH), TEXT(TANK_PATH), 512, 96, 16, 3, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY1_PATH), TEXT(ENEMY1_PATH), 117, 64, 3, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY2_PATH), TEXT(ENEMY2_PATH), 231, 62, 11, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY3_PATH), TEXT(ENEMY3_PATH), 209, 64, 11, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(MID_ENEMY1_PATH), TEXT(MID_ENEMY1_PATH), 115, 242, 1, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(MID_ENEMY2_PATH), TEXT(MID_ENEMY2_PATH), 243, 266, 2, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(BOSS_PATH), TEXT(BOSS_PATH), 5580, 372, 30, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(NORMAL_BULLET_PATH), TEXT(NORMAL_BULLET_PATH), 33, 49, 1, 1, true, RGB(255, 0, 255));
    
    AddImage(TEXT(BOMB_PLANE_PATH), TEXT(BOMB_PLANE_PATH), 153, 134, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_MINIBOMB_PATH), TEXT(BOMB_MINIBOMB_PATH), 480, 32, 32, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_EFFECT_PATH), TEXT(BOMB_EFFECT_PATH), 3584, 320, 16, 1, true, RGB(255, 0, 255));


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
