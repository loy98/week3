#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;

#define WINSIZE_X	1080
#define WINSIZE_Y	720


extern HWND g_hWnd;

bool RectInRect(RECT rc1, RECT rc2);
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);

struct Missile {
	POINT _pt;
	RECT _rc;
	int _size = 0;
	bool canUse = true;
	void Draw(HDC hdc);
};

struct Unit {
	POINT _pt;
	RECT _rc;
	int _size = 0;
	bool isDead = false;
	Missile _missile;

	void Draw(HDC hdc);
	void CheckIsDead(Unit other);
};