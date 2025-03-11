#pragma once
//#include "pch.h"
#include "BarrelGameObject.h"
class Tank;
class Missile;
class Enemy;
class BarrelMainGame : public BarrelGameObject
{
public:
	BarrelMainGame();
	~BarrelMainGame();
	void Init();	// override (부모클래스와 같은 함수이름, 로직을 다르게 구현하고 싶을 때)
	// <-> overload (같은 함수 이름, 매개변수 타입과 갯수가 다르면 다른 함수로 처리)
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	int mousePosX = 0, mousePosY = 0;
	wchar_t szText[128];

	Tank* _tank;
	Enemy* _enemies[5];

	int _time = 0;
	bool _isQUsed = true;
	int _bulletCount = 5;
};

