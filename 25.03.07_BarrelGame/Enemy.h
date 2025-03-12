#pragma once
class Missile;
class Tank;
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
	void CreateMissile();

	FPOINT GetPos() { return _pos; }
	void SetAngle(float angle) { _angle = angle; }
	int GetSize() { return _size; }
	int GetDamage() { return _damage; }
	float GetAngle() { return _angle; }
	void SetFire(bool canFire) { _canFire = canFire; }

	void SetHP(int hp) { _hp = hp; }
	Missile* GetMissiles(int index) { return _missiles[index]; }
	bool IsCollision(Tank* target);
private:
	FPOINT _pos;
	float _speed;
	float _angle;
	int _size;
	int _damage;
	int _hp;

	bool _canFire;
	
	bool _isDead = false;
	Missile* _missiles[10] = { nullptr };
	Tank* _target;
};

