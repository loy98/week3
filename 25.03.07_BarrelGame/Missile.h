#pragma once
enum class MissileType
{
	None,
	Q,
	E,
	Fragment,
	Guided
};
class Enemy;
class Missile
{
public:
	Missile();
	~Missile();

	void CreateMissile(FPOINT pt, float angle, MissileType type);
	void CreateFragments(FPOINT pt, float angle, MissileType type);
	bool IsCollision(Enemy& enemy);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	bool GetIsDead() { return _isDead; }
	void SetIsDead(bool isDead) { _isDead = isDead; }
	FPOINT GetPos() { return _pos; }
	void SetTarget(Enemy* target) { _target = target; }
	Enemy* GetTarget() { return _target; }
	MissileType GetType() { return _type; }

private:
	FPOINT _pos{};
	int _size;
	RECT _rc;
	MissileType _type = MissileType::None;

	float _angle;
	float _speed;
	float _dist;
	FPOINT _dir = {1, 1};

	Missile* _fragments[36] = { nullptr };
	int _deadCount = 0;
	bool _isDead = false;

	Enemy* _target = nullptr;
};

