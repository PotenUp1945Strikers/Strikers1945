#pragma once
#include "UI.h"
#include "config.h"

class InGameUI : public UI
{
private:
	int count = 0;
	int interval = 0;

public:
	void Render(HDC hdc) override;
	void SetCount(int count) { this->count = count; }
	void Setinterval(int interval) { this->interval = interval; }

};

