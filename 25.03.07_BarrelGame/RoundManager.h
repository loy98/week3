#pragma once
#include "BarrelGameObject.h"
#include "Enemy.h"

class Tank;
class RoundManager : public BarrelGameObject
{
public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void SetTank(Tank* tank) { _tank = tank; }
	void SetEnemy(Enemy* enemy) { _enemy = enemy; }
	void SetIsEnemyFire(bool b) { _enemy->SetFire(b); }

	void SetEnemyHP() { _enemy->SetHP(_enemyHP); } // 임시 함수 이름

	int GetEnemyFrequency() { return _enemyFrequency; }
	int GetEnemyHP() { return _enemyHP; }
	int GetCurrentRound() { return _currentRound; }
	bool GetIsClear() { return _isClear; }

	void CheckClear();

	void IncreaseFrequency() { _enemyFrequency -= 40; }
	void IncreaseRound() { _currentRound++; }
	void IncreaseEnemyHp() { _enemyHP += 10; }

private:
	Tank* _tank;
	Enemy* _enemy;
	int _enemyFrequency;
	int _enemyHP;
	bool _isEnemyFire;
	int _currentRound;
	int _killToGoal;
	int _isClear;
	wchar_t szText[128];

};

