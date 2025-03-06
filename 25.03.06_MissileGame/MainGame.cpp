#include "pch.h"
#include "MainGame.h"

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::Init()
{
}

void MainGame::Release()
{
}

void MainGame::Update()
{
}

void MainGame::Render(HDC hdc)
{
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		units[playerIndex]._size = 60;
		units[playerIndex]._pt.x = 200;
		units[playerIndex]._pt.y = 350;

		units[EnemyIndex]._size = 60;
		units[EnemyIndex]._pt.x = 900;
		units[EnemyIndex]._pt.y = 350;

		for (int i = 0; i < 2; ++i)
		{
			units[i]._missile._size = 10;
			units[i]._missile._pt.x = units[i]._pt.x;
			units[i]._missile._pt.y = units[i]._pt.y;
		}
		units[EnemyIndex]._missile.canUse = false;
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);
		break;
	case WM_TIMER:
		if (units[EnemyIndex]._pt.y < 50)
			dir = 1;
		else if (units[EnemyIndex]._pt.y > 650)
			dir = -1;

		units[EnemyIndex]._pt.y += 20 * dir;

		if (units[playerIndex].isDead == false)
		{
			units[EnemyIndex]._missile._pt.x -= 20;

			if (units[EnemyIndex]._missile._pt.x < 0)
			{
				units[EnemyIndex]._missile._pt.x = units[EnemyIndex]._pt.x;
				units[EnemyIndex]._missile._pt.y = units[EnemyIndex]._pt.y;
			}
		}
		else
			units[EnemyIndex]._missile.canUse = true;

		if (units[playerIndex]._missile.canUse == false)
			units[playerIndex]._missile._pt.x += 15;
		else
		{
			units[playerIndex]._missile._pt.x = units[playerIndex]._pt.x;
			units[playerIndex]._missile._pt.y = units[playerIndex]._pt.y;
		}

		if (units[playerIndex]._missile._pt.x > 1000)
			units[playerIndex]._missile.canUse = true;

		UpdateMissileRc(units[playerIndex]._missile);
		UpdateMissileRc(units[EnemyIndex]._missile);
		UpdateUnitRc(units[playerIndex]);
		UpdateUnitRc(units[EnemyIndex]);

		for (int i = 0; i < 2; ++i)
			units[i].CheckIsDead(units[(i + 1) % 2]);

		InvalidateRgn(g_hWnd, NULL, true);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'W': case 'w':
			units[playerIndex]._pt.y -= 20;
			break;
		case 'S': case 's':
			units[playerIndex]._pt.y += 20;
			break;
		case ' ':
			if (units[playerIndex].isDead == true)
				break;
			units[playerIndex]._missile.canUse = false;
			break;
		}


		InvalidateRgn(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		for (int i = 0; i < 2; ++i)
		{
			units[i].Draw(hdc);
			if (units[(i + 1) % 2].isDead == false)
				units[i]._missile.Draw(hdc);
		}

		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0); // 창을 끄면 프로그램이 종료됨
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
