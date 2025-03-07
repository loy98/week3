#include "pch.h"
#include "Missile.h"
#include "CommonFunction.h"

Missile::Missile()
{
}

Missile::~Missile()
{
}

void Missile::CreateMissile(int x, int y)
{
	_pos.x = x;
	_pos.y = y;
	_size = 50;
	_speed = 30;
	_rc = { x, y, _size, _size };
}

void Missile::Init()
{
	
}

void Missile::Release()
{
	
}

void Missile::Update()
{
	_pos.x += _speed * cosf(_angle);
	_pos.y -= _speed * sinf(_angle);
}

void Missile::Render(HDC hdc)
{
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
}
