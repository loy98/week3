#include "pch.h"
#include "Tank.h"
#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
Tank::Tank()
{

}

Tank::~Tank()
{
}

void Tank::Init()
{
	_pos.x = WINSIZE_X / 2;
	_pos.y = WINSIZE_Y;
	_size = 100;
	_damage = 10;
	_name = "탱크";
	_rc = GetRectAtCenter(_pos.x, _pos.y, _size, _size);
	
	//포신 초기화
	_barrelSize = 90;
	_barrelEnd.x = _pos.x;
	_barrelEnd.y = _pos.y - _barrelSize;
	_barrelAngle = 3.14f / 4.0f;
}

void Tank::Release()
{
	//메모리 할당한게 있다면, 해제 먼저 해놓는 것이 좋다.
}

void Tank::Update()
{
	_barrelEnd.x = _pos.x + _barrelSize * cosf(_barrelAngle);
	_barrelEnd.y = _pos.y - _barrelSize * sinf(_barrelAngle);
	for (int i = 0; i < 12; ++i)
	{
		if (_missiles[i])
		{
			_missiles[i]->Update();
			if (_missiles[i]->GetIsDead())
			{
				delete _missiles[i];
				_missiles[i] = nullptr;
			}	
		}
	}
}

bool Tank::IsCollision(Enemy* enemy)
{
	for (int i = 0; i < 12; ++i)
	{
		if (_missiles[i])
		{
			float distX = _missiles[i]->GetPos().x - enemy->GetPos().x;
			float distY = _missiles[i]->GetPos().y - enemy->GetPos().y;
			double dist = sqrt(distX * distX + distY * distY);
			if (dist < enemy->GetSize())
			{
				_missiles[i]->SetIsDead(true);
				enemy->SetIsDead(true);
			}
			if (_missiles[i]->GetIsDead())
			{
				delete _missiles[i];
				_missiles[i] = nullptr;
				return true;
			}
		}
	}

	return false;
}

void Tank::Render(HDC hdc)
{
	//몸통
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
	
	//포신
	MoveToEx(hdc, _pos.x, _pos.y, NULL);
	LineTo(hdc, _barrelEnd.x, _barrelEnd.y);
	for (int i = 0; i < 12; ++i)
	{
		if (_missiles[i])
			_missiles[i]->Render(hdc);
	}
}

void Tank::Move()
{
}

void Tank::Fire()
{
	//미사일 초기화
	for (int i = 0; i < 10; ++i)
	{
		if (!_missiles[i])
		{
			_missiles[i] = new Missile;
			_missiles[i]->CreateMissile(_barrelEnd, _barrelAngle, MissileType::None);
			break;
		}
	}

}

void Tank::FireSkillQ()
{
	if (!_missiles[10])
	{
		_missiles[10] = new Missile;
		_missiles[10]->CreateMissile(_barrelEnd, _barrelAngle, MissileType::Q);
	}

}

void Tank::FireSkillE()
{
	if (!_missiles[11])
	{
		_missiles[11] = new Missile;
		_missiles[11]->CreateMissile(_barrelEnd, _barrelAngle, MissileType::E);
	}
}

void Tank::FireGuidedMissile()
{
	for (int i = 0; i < 10; ++i)
	{
		if (!_missiles[i])
		{
			_missiles[i] = new Missile;
			_missiles[i]->CreateMissile(_barrelEnd, _barrelAngle, MissileType::Guided);
			break;
		}
	}
}

void Tank::RotateBarrel(float angle)
{
	_barrelAngle += angle;
}

void Tank::Dead()
{
}
