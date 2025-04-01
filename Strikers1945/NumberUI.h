#pragma once
#include "UI.h"

class NumberUI: public UI
{
private:
	int number = 0;
	int interval = 0;

public:
	void Render(HDC hdc) override;
	void SetNumber(int num) { number = num; }
	void SetInterval(int i) { interval = i; }
};