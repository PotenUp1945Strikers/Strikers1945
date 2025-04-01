#include "NumberUI.h"
#include "Image.h"

void NumberUI::Render(HDC hdc)
{
	if (!image)
		return;

	int num = number;
	int printNum = 0;
	FPOINT pos = renderPos;

	do 
	{
		printNum = num % 10;
		num /= 10;
		image->FrameRender(hdc, pos.x, pos.y, 0, printNum);
		pos.x -= interval;
	} while (num);
}
