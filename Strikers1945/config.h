#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>

#include "KeyManager.h"

using namespace std;

#define WINSIZE_X	600
#define WINSIZE_Y	800
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)
#define MAX_ENEMY_COLUME 5
#define ENEMY_SPACE_LENGTH 70

#define ENEMY_LAUNCH_RADIUS_OPER 2.6f
#define ENEMY_MAX_ANGLE 330


#define BULLET_COOLTIME 1
#define LUANCH_COOLTIME 5

#define ENEMY_MOVE_SPEED 90
#define ENEMY_LAUNCH_SPEED 140
#define PLAYER_SPEED 140
#define BULLET_SPEED 300
#define BOTH_SIDE_ENEMY_MOVE_LENGTH (WINSIZE_X - MAX_ENEMY_COLUME * ENEMY_SPACE_LENGTH) / 4.0f

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
