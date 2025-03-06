#pragma once
#include "GameObject.h"
class MainGame : public GameObject
{
public:
	MainGame();
	~MainGame();
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	void UpdateUnitRc(Unit& unit)
	{
		unit._rc.left = unit._pt.x - unit._size / 2;
		unit._rc.top = unit._pt.y - unit._size / 2;
		unit._rc.right = unit._pt.x + unit._size / 2;
		unit._rc.bottom = unit._pt.y + unit._size / 2;
	}
	void UpdateMissileRc(Missile& unit)
	{
		unit._rc.left = unit._pt.x - unit._size / 2;
		unit._rc.top = unit._pt.y - unit._size / 2;
		unit._rc.right = unit._pt.x + unit._size / 2;
		unit._rc.bottom = unit._pt.y + unit._size / 2;
	}
public:
	HDC hdc;
	PAINTSTRUCT ps;
	HANDLE hTimer;
	//HWND g_hwnd; //윈도우 핸들
	Unit units[2];
	const int playerIndex = 0;
	const int EnemyIndex = 1;
	int dx = 0, dy = 0;
	HPEN MyPen, OldPen;
	HBRUSH MyBrush, OldBrush;
	int dir = 1;

};

