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
	if (_skillQ)
	{
		_skillQ->Update();
		float firstAngle = _skillQ->GetAngle();
		for (int i = 0; i < 36; ++i)
		{
			if (_skillQ->_fragments[i])
				_skillQ->_fragments[i]->Update();

		}
		if (_skillQ->GetDist() > 200 && _isQUsed)
		{
			for (int i = 0; i < 36; ++i)
			{
				//Missile* fragment = _skillQ->_fragments[i];
				LONG x = _skillQ->GetPos().x;
				LONG y = _skillQ->GetPos().y;
				
				_skillQ->_fragments[i] = new Missile;
				_skillQ->_fragments[i]->CreateMissile(x, y, MissileType::Fragment);
				_skillQ->_fragments[i]->SetAngle(firstAngle + DEG_TO_RAD(10*i));
			}
			_isQUsed = false;
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
	if (_skillQ)
	{
		_skillQ->Render(hdc);
		for (int i = 0; i < 36; ++i)
		{
			//Missile* fragment = _skillQ->GetFragment(i);
			if (_skillQ->_fragments[i])
				_skillQ->_fragments[i]->Render(hdc);
		}

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
					_missile[i]->CreateMissile(_tank->GetBarrelEnd().x, _tank->GetBarrelEnd().y, MissileType::None);
					_missile[i]->SetAngle(_tank->GetBarrelAngle());
					break;
				}
			}
			break;
		case 'q': case 'Q':
			if (_skillQ == nullptr)
			{
				_skillQ = new Missile;
				_skillQ->CreateMissile(_tank->GetBarrelEnd().x, _tank->GetBarrelEnd().y, MissileType::Q);
				_skillQ->SetAngle(_tank->GetBarrelAngle());
			}
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
