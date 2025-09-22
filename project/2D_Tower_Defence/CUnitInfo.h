#ifndef __CUNITINFO_H__
#define __CUNITINFO_H__

//#include <Windows.h>
#include "Timer.h"
#include "DefineData.h"
#include "CTower.h"

enum UnitType
{
	ENUM_UNIT_TYPE_NONE = -1,
	ENUM_UNIT_TYPE_WARRIOR = 0,
	ENUM_UNIT_TYPE_ARCHER,
	ENUM_UNIT_TYPE_GUARDIAN
};

class CUnitInfo
{
public:
	CUnitInfo();
	~CUnitInfo();

	SURFACEINFO* GetpSfUnit() { return g_sfUnit; }		// SURFACEINFO ȣ��
	int GetXPos() { return (int)xPos; }						// x��ǥ
	int GetYPos() { return yPos; }						// y��ǥ
	int GetMaxHP() { return maxHP; }
	int GetAttackDamage() { return attackDamage; }
	float GetAttackDelay() { return attackDelay; }
	int GetAttackRange() { return attackRange; }
	int GetMoveSpeed() { return moveSpeed; }
	int GetCost() { return cost; }
	float GetCreateDelay() { return createDelay; }
	float GetCreateDelayTimer() { return createDelayTimer; }
	BOOL GetIsDie() { return m_isDie; }					// ���� �������� ����
	float GetDieAnimTimer() { return dieAnimTimer; }	// ��� �ִϸ��̼� Ÿ�̸�
	int GetDieMana() { return dieMana; }
	int GetDieGold() { return dieGold; }
	int GetLevel() { return unitLevel; }
	int GetLevelUpGold() { return levelUpGold; }
	BOOL GetisGetDieGoldMana() { return m_isGetDieGoldMana; }
	RECT GetRect();

	void SetisGetDieGoldMana() { m_isGetDieGoldMana = TRUE; }
	void SetnAni(int n) { nAni = n; }	// ���� �ִϸ��̼� ����
	void SetLevel(int level);
	void SetLevelOne();
	
	void DrawSurface(HDC dcDst, int nBgX);								// ���� �׸���
	void UpdateAction(Timer timer, CUnitInfo* target[MAX_UNIT_COUNT]);	// �ൿ ������Ʈ (����, �̵�, ���� ����, ���� �� �ִϸ��̼� Ÿ�̸�)
	void Move(Timer timer);						// �̵�
	void Attack(Timer timer);					// ����
	void TakeDamage(int damage, Timer timer);	// ������ �ޱ�
	void HalfHPAnimation(Timer timer);			// ü���� �� ���Ϸ� �������� �� �ִϸ��̼�

	BOOL ColliderCheck(CUnitInfo* enemy[MAX_UNIT_COUNT]);	// �浹 üũ (���� �����Ÿ� �ȿ� ���� ���Դ���)
	float GetTargetLength(float targetX);					// ���� Ÿ����� �Ÿ� ����

	BOOL CanCreateUnit(int mana);							// ���� ���� �����̰� �� �귶���� (������ �� �ִ���)
	void ResetCreateTimer() { createDelayTimer = createDelay; }								// ���� ���� Ÿ�̸� ����
	void CreateTimerUpdate(Timer timer) { if (createDelayTimer > 0)	createDelayTimer -= timer.GetDeltaTime(); }	// ���� ���� Ÿ�̸� ������Ʈ

	void UnitLevelUP();

protected:
	SURFACEINFO	g_sfUnit[5];	// 0: idle,  1: attack,  2~3: take damage(hp ���� ���� �϶� ��),  4: die
	int			nAni;			// ���� �ִϸ��̼�
	float		xPos;			// ������ x��ǥ
	int			yPos;			// ������ y��ǥ

	int			maxHP;				// �ִ� ü��
	int			nowHP;				// ���� ü��
	int			attackDamage;		// ���ݷ�
	float		attackDelay;		// ���� ������
	float		attackDelayTimer;	// ���� ������ Ÿ�̸�
	int			attackRange;		// ���� ����
	float		moveSpeed;			// �̵� �ӵ�

	int			cost;				// ���� ���
	float		createDelay;		// ���� ������
	float		createDelayTimer;	// ���� ������ Ÿ�̸�

	BOOL		m_isPlayer;			// true: �Ʊ� ����,  false: �� ����
	BOOL		m_isDie;			// true: ����,  false: ���
	BOOL		m_isGetDieGoldMana;	// true: ��� ���, ���� ȹ�� �Ϸ�, false: �̿Ϸ�

	CUnitInfo*	pTargetUnit;		// ���� Ÿ�� ����

	float		halfHPAnimTimer;	// ü�� ���� �ִϸ��̼� Ÿ�̸�
	float		dieAnimTimer;		// ��� �ִϸ��̼� Ÿ�̸�
	int			enumUnitType;		// ���� ����

	BOOL		attackTower;		// Ÿ�� ���� ����
	CTower*		targetTower;		// ������ �� Ÿ��

	int			dieGold;			// �����߸� �� ȹ���� �� �ִ� ��
	int			dieMana;			// �����߸� �� ȹ���� �� �ִ� ����

	int			levelUpGold;		// ������ �� �ʿ��� ���
	int			unitLevel;
};

#endif