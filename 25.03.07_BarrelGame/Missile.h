#pragma once
enum class MissileType
{
	None,
	Q,
	E,
	Fragment,
	Guided,
	Enemy
};
class Enemy;
class Missile
{
public:
	Missile();
	~Missile();

	void CreateMissile(FPOINT pt, float angle, MissileType type);
	void CreateFragments(FPOINT pt, float angle, MissileType type);
	bool IsCollision(Enemy* enemy);

	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	
	bool GetIsDead() { return _isDead; }
	FPOINT GetPos() { return _pos; }
	Enemy* GetTarget() { return _target; }
	MissileType GetType() { return _type; }
	int GetSize() { return _size; }
	int GetDamage() { return _damage; }
	
	void SetIsDead(bool isDead) { _isDead = isDead; }
	void SetTarget(Enemy* target) { _target = target; }

private:
	FPOINT _pos{};
	int _size;
	RECT _rc;
	MissileType _type = MissileType::None;

	float _angle;
	float _speed;
	float _dist;
	int _damage;
	FPOINT _dir = {1, 1};

	Missile* _fragments[36] = { nullptr };
	int _deadCount = 0;
	bool _isDead = false;

	Enemy* _target = nullptr;
};

