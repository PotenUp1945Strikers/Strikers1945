#include "UI.h"
#include "ImageManager.h"
#include "TimerManager.h"
void UI::Init()
{
	key = nullptr;
	image = nullptr;
	currFrameX = 0;
	currFrameY = 0;
	renderPos = { 0.0f, 0.0f };
	elapsedTime = 0.0f;
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
	image = nullptr;
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

void UI::SetImage(const wchar_t* key)
{
	image = ImageManager::GetInstance()->GetImage(key);
}
