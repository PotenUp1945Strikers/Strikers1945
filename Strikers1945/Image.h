#pragma once
#include "config.h"

class Image
{
public:
	enum IMAGE_LOAD_TYPE
	{
		Resource,	
		File,		
		Empty,		
		End
	};

	typedef struct tagImageInfo
	{
		DWORD resID;		
		HDC hMemDC;			
		HBITMAP hBitmap;	
		HBITMAP hOldBit;	
		HDC hTempDC;
		HBITMAP hTempBit;
		HBITMAP hOldTemp;
		int width;			
		int height;			
		BYTE loadType;		

		int maxFrameX;
		int maxFrameY;
		int frameWidth;
		int frameHeight;
		int currFrameX;
		int currFrameY;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBitmap = NULL;
			hOldBit = NULL;
			width = 0;
			height = 0;
			loadType = IMAGE_LOAD_TYPE::Empty;

			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			currFrameX = 0;
			currFrameY = 0;
		}
	} IMAGE_INFO, * LPIMAGE_INFO;

private:
	IMAGE_INFO* imageInfo;
	bool isTransparent;
	COLORREF transColor;

public:
	HRESULT Init(int width, int height);

	HRESULT Init(const wchar_t* filePath, int width, int height, 
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	HRESULT Init(const wchar_t* filePath, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTransparent = FALSE, COLORREF transColor = FALSE);

	void Render(HDC hdc, int destX, int destY);
	void RenderBackground(HDC hdc, int destY, int srcY);
	void Render(HDC hdc, int destX, int destY, int frameIndex, bool isFlip = false);
	void FrameRender(HDC hdc, int destX, int destY, int frameX, int frameY, bool isFlip = false);

	void Release();

	inline HDC GetMemDC() {
		if (imageInfo)
		{
			return imageInfo->hMemDC;
		}
		return NULL;
	}

	inline int GetMaxFrameX() { return imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return imageInfo->maxFrameY; }
};

