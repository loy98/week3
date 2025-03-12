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

	void DecreaseHp(int damage) { _hp -= damage; }
	void SetIsDead(bool isDead) { _isDead = isDead; }
	void IncreaseKillCount() { _killCount++; }
private:
	FPOINT _pos{};
	int _size;
	float _damage;
	string _name;
	RECT _rc{};
	int _hp;
	int _maxHp;
	bool _isDead = false;

	FPOINT _barrelEnd;
	int _barrelSize;
	float _barrelAngle;

	//πÃªÁ¿œ
	Missile* _missiles[12] = { nullptr };
	int _killCount = 0;
	wchar_t szText[128];
};


