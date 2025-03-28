#include "ImageManager.h"

void ImageManager::Init()
{
}

void ImageManager::Release()
{
    for (auto& iter : store)
        iter.second->Release();

    store.clear();
}

Image* ImageManager::AddImage(const char* key, const WCHAR* filepath,
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

Image* ImageManager::AddImage(const char* key, const WCHAR* filepath,
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

void ImageManager::DeleteImage(const char* key)
{
    auto iter = store.find(key);

    if (iter == store.end())
        return;

    Image* image = store[key];
    image->Release();
    delete image;

    store.erase(iter);
}

Image* ImageManager::GetImage(const char* key)
{
    return store.find(key) == store.end() ? nullptr : store[key];
}
