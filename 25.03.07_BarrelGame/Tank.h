#pragma once
#include "BarrelGameObject.h"

class Tank : public BarrelGameObject
{
public:
	Tank();
	~Tank();
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Fire();
	void RotateBarrel(float angle);
	void Dead();

	POINT GetBarrelEnd() { return _barrelEnd; }
	float GetBarrelAngle() { return _barrelAngle; }
private:
	POINT _pos{};
	int _size;
	float _damage;
	string _name;
	RECT _rc{};

	POINT _barrelEnd;
	int _barrelSize;
	float _barrelAngle;

	//πÃªÁ¿œ

};


