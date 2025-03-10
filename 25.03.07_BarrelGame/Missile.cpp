#include "pch.h"
#include "Missile.h"
#include "CommonFunction.h"

Missile::Missile()
{
}

Missile::~Missile()
{
}

void Missile::CreateMissile(POINT pt, float angle, MissileType type)
{
	_pos.x = pt.x;
	_pos.y = pt.y;
	_angle = angle;
	
	_size = 10;
	_speed = 50;
	_rc = { pt.x, pt.y, _size, _size };
	_type = type;
	_dist = 0;
}

void Missile::CreateFragments(POINT pt, float angle, MissileType type)
{
	for (int i = 0; i < 36; ++i)
	{
		if (!_fragments[i])
		{
			_fragments[i] = new Missile;
			_fragments[i]->CreateMissile(_pos, _angle + DEG_TO_RAD(i * 10),
				MissileType::Fragment);
		}
	}
}

void Missile::Init()
{
	
}

void Missile::Release()
{
	for (int i = 0; i < 36; ++i)
	{
		if (_fragments[i])
		{
			delete _fragments[i];
			_fragments[i] = nullptr;
		}
	}
}

void Missile::Update()
{
	switch (_type)
	{
	case MissileType::None:
		if (_pos.x > WINSIZE_X || _pos.x < 0 || _pos.y > WINSIZE_Y || _pos.y < 0)
		{
			_deadChecked = true;
			return;
		}
		else
			break;
	case MissileType::Q:
		if (_dist > 200)
			CreateFragments(_pos, _angle, MissileType::Fragment);
		for (int i = 0; i < 36; ++i)
		{
			if (_fragments[i])
			{
				_fragments[i]->Update();
				LONG x = _fragments[i]->_pos.x;
				LONG y = _fragments[i]->_pos.y;
				if (x > WINSIZE_X || x < 0 || y > WINSIZE_Y || y < 0)
				{
					if (_fragments[i]->GetDeadChecked() == false)
					{
						_fragments[i]->SetDeadChecked(true);
						_deadCount++;
					}
				}
			}
		}
		if (_deadCount == 36)
		{
			Release();
			_deadChecked = true;
		}
		break;
	case MissileType::E:
		if (_deadChecked)
			return;
		if (_pos.x <= 0 || _pos.x >= WINSIZE_X)
		{
			_dir.x *= -1;
			_deadCount++;
		}
		if (_pos.y <= 0 || _pos.y >= WINSIZE_Y)
		{
			_dir.y *= -1;
			_deadCount++;
		}
		if (_deadCount == 5)
			_deadChecked = true;
	case MissileType::Fragment:
		if (_deadChecked)
			return;
		else
			break;
	}
	
	_pos.x += _speed * cosf(_angle) * _dir.x;
	_pos.y -= _speed * sinf(_angle) * _dir.y;
	_dist += _speed;
	
	
}

void Missile::Render(HDC hdc)
{
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
	if (_type != MissileType::Q)
		return;
	for (int i = 0; i < 36; ++i)
	{
		if (_fragments[i])
			_fragments[i]->Render(hdc);
	}
}
