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

	void CreateMissile(POINT pt, float angle, MissileType type);
	void CreateFragments(POINT pt, float angle, MissileType type);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	bool GetDeadChecked() { return _deadChecked; }
	void SetDeadChecked(bool isDead) { _deadChecked = isDead; }

private:
	POINT _pos{};
	int _size;
	RECT _rc;
	MissileType _type = MissileType::None;

	float _angle;
	float _speed;
	float _dist;
	POINT _dir = {1, 1};

	Missile* _fragments[36] = { nullptr };
	int _deadCount = 0;
	bool _deadChecked = false;
};

