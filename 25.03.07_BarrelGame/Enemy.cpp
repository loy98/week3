#include "pch.h"
#include "Enemy.h"
#include "Missile.h"
#include "Tank.h"
#include "CommonFunction.h"
#include <cstdlib>
#include <ctime>

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	_pos.x = rand() % WINSIZE_X;
	_pos.y = 0;

	_size = 20;
	_speed = 10;
	_damage = 20;

	_canFire = false;
}

void Enemy::Update()
{
	Move();
	for (int i = 0; i < 10; ++i)
	{
		if (_missiles[i])
			_missiles[i]->Update();
	}
}

void Enemy::Render(HDC hdc)
{
	if (_isDead)
		return;
	RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
	for (int i = 0; i < 10; ++i)
	{
		if (_missiles[i])
			_missiles[i]->Render(hdc);
	}
}

void Enemy::Move()
{
	_pos.x += _speed * cos(_angle);
	_pos.y -= _speed * sin(_angle);
}

void Enemy::CreateMissile()
{
	if (_canFire) {
		for (int i = 0; i < 10; ++i)
		{
			if (!_missiles[i])
			{
				_missiles[i] = new Missile;
				_missiles[i]->CreateMissile(_pos, _angle, MissileType::Enemy);
				break;
			}
		}
	}
}

bool Enemy::IsCollision(Tank* target)
{
	if (!this)
		return false;
	for (int i = 0; i < 10; ++i)
	{
		if (_missiles[i])
		{
			float distX = _missiles[i]->GetPos().x - target->GetPos().x;
			float distY = _missiles[i]->GetPos().y - target->GetPos().y;
			double dist = sqrt(distX * distX + distY * distY);
			if (dist < (target->GetSize() + _missiles[i]->GetSize())/2)
			{
				_missiles[i]->SetIsDead(true);
				target->DecreaseHp(_missiles[i]->GetDamage());
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