#pragma once
#include "BarrelGameObject.h"
class Missile;
class Enemy;
class Tank : public BarrelGameObject
{
public:
	Tank();
	~Tank();
	void Init();
	void Release();
	void Update();
	bool IsCollision(Enemy* enemy);
	void Render(HDC hdc);

	void Move();
	void Fire();
	void FireSkillQ();
	void FireSkillE();
	void FireGuidedMissile();
	void RotateBarrel(float angle);
	void Dead();

	FPOINT GetBarrelEnd() { return _barrelEnd; }
	float GetBarrelAngle() { return _barrelAngle; }
	FPOINT GetPos() { return _pos; }
	int GetSize() { return _size; }
	bool GetIsDead() { return _isDead; }
	Missile* GetMissiles(int index) { return _missiles[index]; }

	void SetIsDead(bool isDead) { _isDead = isDead; }
private:
	FPOINT _pos{};
	int _size;
	float _damage;
	string _name;
	RECT _rc{};
	bool _isDead = false;

	FPOINT _barrelEnd;
	int _barrelSize;
	float _barrelAngle;

	//�̻���
	Missile* _missiles[12] = { nullptr };
	
};


