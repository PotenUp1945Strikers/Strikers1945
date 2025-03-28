#include "InGameUI.h"
#include "ImageManager.h"

void InGameUI::Render(HDC hdc)
{
	for (int i = 0; i < count; i++)
	{
		image->FrameRender(hdc, renderPos.x + (length * i), renderPos.y, currFrameX, currFrameY, false);
	}
}
