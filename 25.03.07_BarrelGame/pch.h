#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
using namespace std;

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define PI 3.141592
#define DEG_TO_RAD(degree) degree* PI / 180
extern HWND g_hWnd;

struct FPOINT
{
	float x;
	float y;

	bool operator==(FPOINT& other)
	{
		return (x == other.x) && (y == other.y);
	}
};


