#pragma once
class Missile;
class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Render(HDC hdc);

	void Move();
	void SetIsDead(bool isDead) { _isDead = isDead; }

	FPOINT GetPos() { return _pos; }
	void SetAngle(float angle) { _angle = angle; }
	int GetSize() { return _size; }
private:
	FPOINT _pos;
	float _speed;
	float _angle;
	int _size;

	bool _isDead = false;
};

