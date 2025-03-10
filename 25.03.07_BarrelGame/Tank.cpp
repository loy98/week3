#include "pch.h"
#include "Tank.h"
#include "Missile.h"
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
	_name = "��ũ";
	_rc = GetRectAtCenter(_pos.x, _pos.y, _size, _size);
	
	//���� �ʱ�ȭ
	_barrelSize = 90;
	_barrelEnd.x = _pos.x;
	_barrelEnd.y = _pos.y - _barrelSize;
	_barrelAngle = 3.14f / 4.0f;
	

}

void Tank::Release()
{
	//�޸� �Ҵ��Ѱ� �ִٸ�, ���� ���� �س��� ���� ����.
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
			if (_missiles[i]->GetDeadChecked())
			{
				delete _missiles[i];
				_missiles[i] = nullptr;
			}	
		}
	}
}

void Tank::Render(HDC hdc)
{
	//����
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
	
	//����
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
	//�̻��� �ʱ�ȭ
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

void Tank::RotateBarrel(float angle)
{
	_barrelAngle += angle;
}

void Tank::Dead()
{
}
