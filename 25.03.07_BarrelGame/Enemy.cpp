#include "pch.h"
#include "Enemy.h"
#include "Missile.h"
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
}

void Enemy::Update()
{
}

void Enemy::Render(HDC hdc)
{
	if (!_isDead)
		RenderEllipseAtCenter(hdc, _pos.x, _pos.y, _size, _size);
}

void Enemy::Move()
{
	_pos.x += _speed * cos(_angle);
	_pos.y -= _speed * sin(_angle);
}

