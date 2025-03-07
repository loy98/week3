#pragma once
enum class MissileType
{
	None,
	Q,
	E,
	Fragment
};
class Missile
{
public:
	Missile();
	~Missile();

	void CreateMissile(int x, int y, MissileType type);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	float GetAngle() { return _angle; }
	void SetAngle(float angle) { _angle = angle; }
	POINT GetPos() { return _pos; }
	float GetDist() { return _dist; }
	Missile* GetFragment(int index) { return _fragments[index]; }
	Missile* _fragments[36] = { nullptr };

private:
	POINT _pos{};
	int _size;
	RECT _rc;
	MissileType _type = MissileType::None;

	float _angle;
	float _speed;
	float _dist;

	
};

