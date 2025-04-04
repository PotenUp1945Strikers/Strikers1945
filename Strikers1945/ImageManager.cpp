#include "ImageManager.h"

void ImageManager::Init()
{
    AddImage(TEXT(BACKGROUND_PATH), TEXT(BACKGROUND_PATH), WINSIZE_X, BACKGROUND_SIZE,1,1,true,RGB(255,0,255));
    AddImage(TEXT(BACKGROUND_CLOUD_PATH), TEXT(BACKGROUND_CLOUD_PATH), WINSIZE_X, 3370, 1, 1, true, RGB(255, 0, 255));

    AddImage(TEXT(OPENING_PATH), TEXT(OPENING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PAUSE_PATH), TEXT(PAUSE_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(GAMEOVER_PATH), TEXT(GAMEOVER_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ENDING_PATH), TEXT(ENDING_PATH), WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(LIFE_COUNT_PATH), TEXT(LIFE_COUNT_PATH), 21, 31, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PlAYER2_LIFE_COUNT_PATH), TEXT(PlAYER2_LIFE_COUNT_PATH), 21, 31, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_COUNT_PATH), TEXT(BOMB_COUNT_PATH), 23, 32, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NUMBER_SET1_PATH), TEXT(NUMBER_SET1_PATH), 38, 380, 1, 10, true, RGB(255, 0, 255));

    AddImage(TEXT(PLAYER_PATH), TEXT(PLAYER_PATH), 448, 62, 7, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PLAYER2_PATH), TEXT(PLAYER2_PATH), 448, 62, 7, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(TANK_PATH), TEXT(TANK_PATH), 1024, 192, 16, 3, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY1_PATH), TEXT(ENEMY1_PATH), 234, 128, 3, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY2_PATH), TEXT(ENEMY2_PATH), 462, 124, 11, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(ENEMY3_PATH), TEXT(ENEMY3_PATH), 418, 128, 11, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(MID_ENEMY1_PATH), TEXT(MID_ENEMY1_PATH), 230, 484, 1, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(MID_ENEMY2_PATH), TEXT(MID_ENEMY2_PATH), 486, 532, 2, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(BOSS_PATH), TEXT(BOSS_PATH), 13950, 930, 30, 2, true, RGB(255, 0, 255));

    AddImage(TEXT(PLAYER_BULLET1_PATH), TEXT(PLAYER_BULLET1_PATH), 264, 98, 4, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PLAYER_BULLET2_PATH), TEXT(PLAYER_BULLET2_PATH), 264, 98, 4, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PLAYER_BULLET3_PATH), TEXT(PLAYER_BULLET3_PATH), 264, 98, 4, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(PLAYER_BULLET4_PATH), TEXT(PLAYER_BULLET4_PATH), 264, 98, 4, 1, true, RGB(255, 0, 255));

    AddImage(TEXT(HIT_EFFECT_PATH), TEXT(HIT_EFFECT_PATH), 120, 40, 3, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(TARGETTING_BULLET_PATH), TEXT(TARGETTING_BULLET_PATH), 24, 24, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(AROUND_BULLET_PATH), TEXT(AROUND_BULLET_PATH), 25, 25, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(RANDOM_BULLET_PATH), TEXT(RANDOM_BULLET_PATH), 378, 108, 7, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(RAPIDFIRE_BULLET_PATH), TEXT(RAPIDFIRE_BULLET_PATH), 32, 32, 1, 1, true, RGB(255, 0, 255));


    //AddImage(TEXT(BOMB_EFFECT_PATH), TEXT(BOMB_EFFECT_PATH), 512, 256, 4, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_EFFECT2_PATH), TEXT(BOMB_EFFECT2_PATH), 672, 1600, 3, 5, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT1_PATH), TEXT(EFFECT1_PATH), 512, 1536, 2, 6, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT2_PATH), TEXT(EFFECT2_PATH), 576, 48, 12, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT3_PATH), TEXT(EFFECT3_PATH), 512, 128, 8, 2, true, RGB(255, 0, 255));
    AddImage(TEXT(EFFECT4_PATH), TEXT(EFFECT4_PATH), 512, 384, 4, 3, true, RGB(255, 0, 255));
    
    
    AddImage(TEXT(BOMB_PLANE_PATH), TEXT(BOMB_PLANE_PATH), 153, 134, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_MINIBOMB_PATH), TEXT(BOMB_MINIBOMB_PATH), 480, 32, 32, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(BOMB_EFFECT_PATH), TEXT(BOMB_EFFECT_PATH), 640, 640, 4, 4, true, RGB(0, 248, 0));
    //AddImage(TEXT(BOMB_EFFECT_PATH), TEXT(BOMB_EFFECT_PATH), 3584, 320, 16, 1, true, RGB(0, 248, 0));
    AddImage(TEXT(ITEM_HOVERBOMB_PATH), TEXT(ITEM_HOVERBOMB_PATH), 480, 30, 8, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ITEM_HOVERPOWERUP_PATH), TEXT(ITEM_HOVERPOWERUP_PATH), 258, 30, 6, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(ITEM_HOVERMEDAL_PATH), TEXT(ITEM_HOVERMEDAL_PATH), 240, 59, 8, 1, true, RGB(255, 0, 255));


    AddImage(TEXT(ITEM_EFFECT_PATH), TEXT(ITEM_EFFECT_PATH), 576, 288, 8, 4, true, RGB(255, 0, 255));

    AddImage(TEXT(NORMAL_MISSILE1_PATH), TEXT(NORMAL_MISSILE1_PATH), 9, 24, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NORMAL_MISSILE2_PATH), TEXT(NORMAL_MISSILE2_PATH), 11, 26, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NORMAL_MISSILE3_PATH), TEXT(NORMAL_MISSILE3_PATH), 21, 32, 1, 1, true, RGB(255, 0, 255));
    AddImage(TEXT(NORMAL_MISSILE4_PATH), TEXT(NORMAL_MISSILE4_PATH), 27, 47, 1, 1, true, RGB(255, 0, 255));


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
