#pragma once
#include "UI.h"
#include "config.h"

class InGameUI : public UI
{
private:
	PlayerNum playerNum = PlayerNum::NONE; 
	int count = 0;
	int interval = 0;

public:
	void Render(HDC hdc) override;
	void SetCount(int count) { this->count = count; }
	void Setinterval(int interval) { this->interval = interval; }

	void SetPlayerNum(PlayerNum playerNum) { this->playerNum = playerNum; }


};

