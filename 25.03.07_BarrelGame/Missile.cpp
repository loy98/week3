#include "pch.h"
#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"

Missile::Missile()
{
}

Missile::~Missile()
{
}

void Missile::CreateMissile(FPOINT pt, float angle, MissileType type)
{
	_pos.x = pt.x;
	_pos.y = pt.y;
	_angle = angle;
	
	_size = 20;
	_speed = 20;
	_rc = { (long)pt.x, (long)pt.y, _size, _size };
	_type = type;
	_dist = 0;
}

void Missile::CreateFragments(FPOINT pt, float angle, MissileType type)
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

bool Missile::IsCollision(Enemy& enemy)
{
	double distX = _pos.x - enemy.GetPos().x;
	double distY = _pos.y - enemy.GetPos().y;
	double dist = sqrt(distX * distX + distY * distY);
	if (dist < enemy.GetSize())
		return true;

	return false;
}

void Missile::Init()
{
	
}

void Missile::Release()
{
	for (int i = 0; i < 36; ++i) {
		if (_fragments[i]) {
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
		if (_pos.x > WINSIZE_X || _pos.x < 0 || _pos.y > WINSIZE_Y || _pos.y < 0) {
			_isDead = true;	return;
		}
		else
			break;
	case MissileType::Q:
		if (_dist > 200)	
			CreateFragments(_pos, _angle, MissileType::Fragment);
		for (int i = 0; i < 36; ++i) {
			if (_fragments[i]) {
				_fragments[i]->Update();
				LONG x = _fragments[i]->_pos.x;
				LONG y = _fragments[i]->_pos.y;
				if (x > WINSIZE_X || x < 0 || y > WINSIZE_Y || y < 0) {
					if (_fragments[i]->GetIsDead() == false) {
						_fragments[i]->SetIsDead(true);
						_deadCount++;
					}
				}
			}
		}
		if (_deadCount == 36) {
			Release();
			_isDead = true;
		}
		break;
	case MissileType::E:
		if (_isDead)
			return;
		if (_pos.x <= 0 || _pos.x >= WINSIZE_X) {
			_dir.x *= -1;
			_deadCount++;
		}
		if (_pos.y <= 0 || _pos.y >= WINSIZE_Y) {
			_dir.y *= -1;
			_deadCount++;
		}
		if (_deadCount == 5)
			_isDead = true;
		break;
	case MissileType::Fragment:
		if (_isDead)
			return;
		else
			break;
	case MissileType::Guided:
		if (_isDead)
			return;
		if (_target)
		{
			float distX = _target->GetPos().x - _pos.x;
			float distY = _target->GetPos().y - _pos.y;
			float dist = sqrt(distX * distX + distY * distY);
			_dir = { distX / dist, -distY / dist };
			_pos.x += _speed * _dir.x;
			_pos.y -= _speed * _dir.y;
		}
		if (_pos.x > WINSIZE_X || _pos.x < 0 || _pos.y > WINSIZE_Y || _pos.y < 0) {
			_isDead = true;	return;
		}
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
