#pragma once
#include "Singleton.h"

class EventHandler: public Singleton<EventHandler>
{
public:
	static void Update();
};

