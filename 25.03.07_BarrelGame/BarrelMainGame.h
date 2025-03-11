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
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
	// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
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

