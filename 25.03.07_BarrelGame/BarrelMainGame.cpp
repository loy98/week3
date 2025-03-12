#include "pch.h"
#include "BarrelMainGame.h"
#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"
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
	FPOINT tankPos = _tank->GetPos();
	for (int i = 0; i < 5; ++i)
	{
		if (!_enemies[i] && _time == 0)
		{
			_enemies[i] = new Enemy;
			_enemies[i]->Init();
			FPOINT pt = _enemies[i]->GetPos();
			_enemies[i]->SetAngle(3.141592 - atan2(pt.y - tankPos.y, pt.x - tankPos.x));
			
			break;
		}
		if (_enemies[i])
		{
			_enemies[i]->Update();
			if (_missileTime == 0)
				_enemies[i]->CreateMissile();
		}
	}
	
	for (int i = 0; i < 5; ++i)
	{
		if (!_enemies[i])
			continue;
		double distX = tankPos.x - _enemies[i]->GetPos().x;
		double distY = tankPos.y - _enemies[i]->GetPos().y;
		double dist = sqrt(distX * distX + distY * distY);
		/*if (dist <= _tank->GetSize())
		{
			_tank->SetIsDead(true);
			break;
		}*/
		if (_tank->IsCollision(_enemies[i]))
		{
			_tank->IncreaseKillCount();
			delete _enemies[i];
			_enemies[i] = nullptr;
		}
		_enemies[i]->IsCollision(_tank);

	}
	
	for (int i = 0; i < 12; ++i)
	{
		Missile* missile = _tank->GetMissiles(i);
  		if (!missile)
			continue;
		for (int j = 0; j < 5; ++j)
		{
			if (missile->GetType() == MissileType::Guided && _enemies[j])
			{
				if (missile->GetTarget())
					continue;
				else
				{
					missile->SetTarget(_enemies[j]);
					break;
				}
			}
		}
	}
}

void BarrelMainGame::Render(HDC hdc)
{
	wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
	TextOut(hdc, 20, 60, szText, wcslen(szText));
	if (!_tank->GetIsDead())
		_tank->Render(hdc);
	for (int i = 0; i < 5; ++i)
	{
		if (_enemies[i])
			_enemies[i]->Render(hdc);
	}
}

LRESULT BarrelMainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 50, NULL);
		srand(static_cast<unsigned int>(time(nullptr)));
		break;
	case WM_TIMER:
		if (_tank->GetIsDead())
			break;
		this->Update();
		if (_time < 0)
			_time = 50;
		_time--;
		if (_missileTime < 0)
			_missileTime = 20;
		_missileTime--;
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
			if (_bulletCount == 0)
			{
				_bulletCount = 5;
				_tank->FireGuidedMissile();
			}
			else
				_tank->Fire();
			_bulletCount--;
			break;
		case 'q': case 'Q':
			_tank->FireSkillQ();
			break;
		case 'e': case'E':
			_tank->FireSkillE();
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
