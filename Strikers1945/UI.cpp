#include "UI.h"
#include "ImageManager.h"
#include "TimerManager.h"
void UI::Init()
{
	image = nullptr;
	currFrameX = 0;
	currFrameY = 0;
	renderPos = { 0.0f, 0.0f };
}

void UI::Init(FPOINT renderPos)
{
	image = nullptr;
	currFrameX = 0;
	currFrameY = 0;
	this->renderPos = { renderPos.x, renderPos.y };
}

void UI::Release()
{
}

void UI::Update()
{
	elapsedTime += TimerManager::GetInstance()->GetDeltaTime();
	if (elapsedTime > 0.1f)
	{
		currFrameX++;
		if (currFrameX > image->GetMaxFrameX())
		{
			currFrameX = 0;
			currFrameY++;
			if (currFrameY > image->GetMaxFrameY())
			{
				currFrameY = 0;
			}
		}
		elapsedTime = 0.0f;
	}

}

void UI::Render(HDC hdc)
{
	if(image)
		image->Render(hdc, renderPos.x, renderPos.y, 0);
}

void UI::SetImage(const wchar_t* filePath, int width, int height, int maxFrameX, int maxFrameY)
{
	key = filePath;
	image = ImageManager::GetInstance()->AddImage(key, filePath, width, height, maxFrameX, maxFrameY, true, RGB(255, 0, 255));
}
