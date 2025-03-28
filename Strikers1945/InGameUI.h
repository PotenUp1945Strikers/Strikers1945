#pragma once
#include "UI.h"
#include "config.h"

class InGameUI : public UI
{
private:
	int count;
	int length;

public:
	void Render(HDC hdc) override;
	void SetCount(int count) { this->count = count; }

};

