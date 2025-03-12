#include "pch.h"
#include "RoundManager.h"
#include "Tank.h"
#include "Enemy.h"

void RoundManager::Init()
{
	_enemyFrequency = 50;
	_enemyHP = 50;
	_isEnemyFire = false;
	_currentRound = 1;
	_killToGoal = 10;
	_isClear = false;

}

void RoundManager::Release()
{
	delete _tank;
	delete _enemy;
}

void RoundManager::Update()
{
	CheckClear();
	SetIsEnemyFire(_isEnemyFire);
}

void RoundManager::Render(HDC hdc)
{
	wsprintf(szText, TEXT("현재 라운드: %d, 목표 : %d / %d"), _currentRound, _tank->GetKillCount(), _killToGoal);
	TextOut(hdc, 800, 60, szText, wcslen(szText));
}

void RoundManager::CheckClear()
{
	if (_killToGoal <= _tank->GetKillCount())
	{
		// 난이도 수정
		switch (_currentRound)
		{
		case 1:
			IncreaseFrequency();
			break;
		case 2:
			_isEnemyFire = true;
			break;
		case 3:
			_isClear = true;
			break;
		default:
			break;
		}
		IncreaseEnemyHp();
		IncreaseRound();

		// 난이도 적용
		_tank->Init();
		SetEnemyHP();
		//SetEnemyCanFire();
	}
}



