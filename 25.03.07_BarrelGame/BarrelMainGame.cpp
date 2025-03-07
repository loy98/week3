#include "pch.h"
#include "BarrelMainGame.h"
#include "Tank.h"
#include "Missile.h"
BarrelMainGame::BarrelMainGame()
{
}

BarrelMainGame::~BarrelMainGame()
{
}

void BarrelMainGame::Init()
{
	_tank = new Tank;
	_tank->Init();
}

void BarrelMainGame::Release()
{
	if (_tank)
	{
		_tank->Release();
		delete _tank;
	}
}

void BarrelMainGame::Update()
{
	if (_tank)
		_tank->Update();
	for (int i = 0; i < 10; ++i)
	{
		if (_missile[i] != nullptr)
		{
			_missile[i]->Update();
			LONG x = _missile[i]->GetPos().x;
			LONG y = _missile[i]->GetPos().y;
			if (x < 0 || x > WINSIZE_X || y < 0 || y > WINSIZE_Y)
			{
				delete _missile[i];
				_missile[i] = nullptr;
			}
		}
	}
}

void BarrelMainGame::Render(HDC hdc)
{
	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hdc, 20, 60, szText, wcslen(szText));
	_tank->Render(hdc);
	for (int i = 0; i < 10; ++i)
	{
		if (_missile[i])
			_missile[i]->Render(hdc);
		else
			continue;
	}
}

LRESULT BarrelMainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);

		break;
	case WM_TIMER:
		this->Update();
		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a' : case 'A':
			_tank->RotateBarrel(DEG_TO_RAD(5));
			break;
		case 'd': case 'D':
			_tank->RotateBarrel(DEG_TO_RAD(-5));
			break;
		case ' ':
			for (int i = 0; i < 10; ++i)
			{
				if (_missile[i] == nullptr)
				{
					_missile[i] = new Missile;
					_missile[i]->CreateMissile(_tank->GetBarrelEnd().x, _tank->GetBarrelEnd().y);
					_missile[i]->SetAngle(_tank->GetBarrelAngle());
					break;
				}
				else
					continue;
			}
		case 'q': case 'Q':
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		this->Render(hdc);
		
		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
