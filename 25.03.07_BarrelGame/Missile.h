#pragma once
class Missile
{
public:
	Missile();
	~Missile();

	void CreateMissile(int x, int y);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	void SetAngle(float angle) { _angle = angle; }
	POINT GetPos() { return _pos; }
private:
	POINT _pos{};
	int _size;
	RECT _rc;

	float _angle;
	float _speed;
};

