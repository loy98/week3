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
}

void Tank::Render(HDC hdc)
{
	//몸통
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
	
	//포신
	MoveToEx(hdc, _pos.x, _pos.y, NULL);
	LineTo(hdc, _barrelEnd.x, _barrelEnd.y);
}

void Tank::Move()
{
}

void Tank::Fire()
{
	/*for (int i = 0; i < 10; ++i)
	{
		if (_missile[i] == nullptr)
		{
			_missile[i] = new Missile;
			_missile[i]->CreateMissile(_barrelEnd.x, _barrelEnd.y);
			_missile[i]->SetAngle(_barrelAngle);
			break;
		}
	}*/
}

void Tank::RotateBarrel(float angle)
{
	_barrelAngle += angle;
}

void Tank::Dead()
{
}
