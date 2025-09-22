#ifndef __CTOWER_H__
#define __CTOWER_H__

//#include <Windows.h>
#include "DefineData.h"
#include "Timer.h"
#include "CTowerWizard.h"

class CTower
{
public:
	CTower();
	CTower(BOOL player, int level);
	~CTower();

	SURFACEINFO* GetpSfUnit() { return g_sfTower; }
	CTowerWizard* GetTowerWizard() { return &towerWizard; }
	int GetMaxHP() { return maxHP; }
	int GetDefenceLine() { return defenceLine; }
	void SetMaxHP(int hp) { maxHP = hp;		nowHP = maxHP; }
	void SetTowerState(int state) { towerState = state; }
	void SetxPos(int x) { xPos = x; }
	void SetDefenceLine(BOOL leftTower);
	void SetLevelOne();

	void UpdateTower(Timer timer);
	void DrawSurface(HDC dcDst, int nBgX);				// Ÿ�� �׸���
	void PrintTowerHP(HDC dcDst, int nBgX);				// Ÿ�� ü�� ǥ��
	void TakeDamage(int dmg, Timer timer);

	BOOL TowerHPZero();
	void ResetTower();
	void TowerMaxHPLevelUp() { maxHP += 500;	nowHP = maxHP; }

private:
	SURFACEINFO	g_sfTower[3];			// 0: �⺻,  1: ���ݹ���,  2: �ı�
	int			towerState;				// 0: �⺻,  1: ���ݹ���,  2: �ı�
	int			xPos;					// Ÿ���� x��ǥ
	int			yPos;					// Ÿ���� y��ǥ
	int			hpXPos;					// Ÿ�� hp ǥ�� x��ǥ
	int			hpYPos;					// Ÿ�� hp ǥ�� y��ǥ
	int			maxHP;					// �ִ� ü��
	int			nowHP;					// ���� ü��
	int			defenceLine;			// Ÿ���� ��, ��� ������ �����ϴ� ����
	float		takeDamageStateDelay;	// �������� �޾� ���� ������ ���ߴٰ� ������� ���ƿ��� �ð�
	float		takeDamageStateTimer;	// takeDamageStateDelay Ÿ�̸�
	CTowerWizard	towerWizard;		
};

#endif