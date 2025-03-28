#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

using namespace std;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

#define PAUSE_KEY 'P'
#define REGAME_KEY 'R'

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

enum class GameStates: UINT8
{
	Intro,
	InGame,
	Pause,
	Ending
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
