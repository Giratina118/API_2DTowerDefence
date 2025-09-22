#include <stdio.h>
#include "PaintScreen.h"
#include "ImageManager.h"
#include "UpdateGameProc.h"

extern SURFACEINFO g_sfBack;

void PaintTitleScreen(BOOL* buttonClick, SURFACEINFO* g_sfBG, SURFACEINFO* g_sfTitle, SURFACEINFO* g_sfRectBtn, int nBgX, HFONT* newFont, HFONT* oldFont)
{
	__PutStretch(g_sfBack.dcSurface, nBgX, 0, MAP_SIZE_RATE, MAP_SIZE_RATE, g_sfBG);	// ���
	__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 250, 20, g_sfTitle, 500, 200);	// Ÿ��Ʋ �̹���

	if (buttonClick[0])	__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 250, &g_sfRectBtn[1], 300, 70);	// �̾��ϱ� ��ư
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 250, &g_sfRectBtn[0], 300, 70);

	if (buttonClick[1]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 325, &g_sfRectBtn[1], 300, 70);	// ���ν��� ��ư
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 325, &g_sfRectBtn[0], 300, 70);

	if (buttonClick[2]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 400, &g_sfRectBtn[3], 300, 70);	// ���� ��ư
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 150, 400, &g_sfRectBtn[2], 300, 70);

	// ���� ���
	SetBkMode(g_sfBack.dcSurface, TRANSPARENT);
	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));

	*newFont = CreateFont(40, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);

	TextOut(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 90, 265, "Load Game", strlen("Load Game"));
	TextOut(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 78, 340, "New Game", strlen("New Game"));
	TextOut(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 25, 415, "Exit", strlen("Exit"));

	SelectObject(g_sfBack.dcSurface, *oldFont);
	DeleteObject(*newFont);
}

void PainrReadyScreen(BOOL* buttonClick, SURFACEINFO* g_sfBG, SURFACEINFO* g_sfRectBtn, int nBgX, HFONT* newFont, HFONT* oldFont, int stageLevel, int gold, CUnitInfo* g_infoUnit, 
	SURFACEINFO* g_sfUpgradeBtn, int* upgradeLevel, int* upgradeGold, CTower* g_objTower, SURFACEINFO* g_sfMana, int maxMana, float manaDelay, SURFACEINFO* g_sfTowerIcon)
{
	__PutStretch(g_sfBack.dcSurface, nBgX, 0, MAP_SIZE_RATE, MAP_SIZE_RATE, g_sfBG);			// ���

	if (buttonClick[3]) __PutSprite(g_sfBack.dcSurface, 100, 230, &g_sfRectBtn[1], 200, 60);	// ����
	else				__PutSprite(g_sfBack.dcSurface, 100, 230, &g_sfRectBtn[0], 200, 60);

	if (buttonClick[4]) __PutSprite(g_sfBack.dcSurface, 100, 330, &g_sfRectBtn[3], 200, 60);	// Ÿ��Ʋ�� ���ư���
	else				__PutSprite(g_sfBack.dcSurface, 100, 330, &g_sfRectBtn[2], 200, 60);

	TextOut(g_sfBack.dcSurface, 126, 248, "Stage Start", strlen("Stage Start"));
	TextOut(g_sfBack.dcSurface, 177, 348, "Back", strlen("Back"));

	// ���� �������� ���
	SetBkMode(g_sfBack.dcSurface, TRANSPARENT);
	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));

	*newFont = CreateFont(25, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	char printStage[32];
	wsprintf(printStage, "Stage %d", stageLevel);
	TextOut(g_sfBack.dcSurface, 150, 150, printStage, strlen(printStage));

	// ��� �߾� ���׷��̵� ����
	TextOut(g_sfBack.dcSurface, 470, 10, "Upgrade", strlen("Upgrade"));

	// ���
	SetTextColor(g_sfBack.dcSurface, RGB(200, 200, 50));
	char printGold[32];
	wsprintf(printGold, "Gold: %d", gold);
	TextOut(g_sfBack.dcSurface, 1000, 10, printGold, strlen(printGold));

	// ���׷��̵� ���� �ؽ�Ʈ
	*newFont = CreateFont(18, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));

	// ���� ���׷��̵�
	UpgradeUnitInfoPrint(g_infoUnit[0], 400, 40, &g_sfBack.dcSurface, g_sfUpgradeBtn);	// ����
	UpgradeUnitInfoPrint(g_infoUnit[2], 675, 40, &g_sfBack.dcSurface, g_sfUpgradeBtn);	// �ü�
	UpgradeUnitInfoPrint(g_infoUnit[4], 950, 40, &g_sfBack.dcSurface, g_sfUpgradeBtn);	// ���к�


	// ���׷��̵�: ������(���ݷ�, ��Ÿ�, �����ֱ�), ����(�ִ� ����, ���� ȸ�� �ӵ�), Ÿ�� ü��
	char upgradeInfoText[32];

	// ������ ���ݷ�
	UpgradeAbilityInfoPrint(400, 200, "Attack Damage", 0, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);											// �̸�
	__PutSprite(g_sfBack.dcSurface, 415, 210, &g_objTower[0].GetTowerWizard()->GetpSfWizard()[0]);	// �׸�

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	wsprintf(upgradeInfoText, "%d", g_objTower[0].GetTowerWizard()->GetAttackDamage());				// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 400 + 110, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[0] < 10)
	{
		wsprintf(upgradeInfoText, "%d", g_objTower[0].GetTowerWizard()->GetAttackDamage() + 4);		// ���� ���� ����
		TextOut(g_sfBack.dcSurface, 400 + 175, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	// ������ ��Ÿ�
	UpgradeAbilityInfoPrint(675, 200, "Attack Range", 1, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);
	__PutSprite(g_sfBack.dcSurface, 690, 210, &g_objTower[0].GetTowerWizard()->GetpSfWizard()[0]);

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	wsprintf(upgradeInfoText, "%d", g_objTower[0].GetTowerWizard()->GetAttackRange());				// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 675 + 105, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[1] < 10)
	{
		wsprintf(upgradeInfoText, "%d", g_objTower[0].GetTowerWizard()->GetAttackRange() + 20);		// ���� ���� ����
		TextOut(g_sfBack.dcSurface, 675 + 175, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	// ������ ���� �ӵ�
	UpgradeAbilityInfoPrint(950, 200, "Attack Delay", 2, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);
	__PutSprite(g_sfBack.dcSurface, 965, 210, &g_objTower[0].GetTowerWizard()->GetpSfWizard()[0]);

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	sprintf_s(upgradeInfoText, "%.2f", g_objTower[0].GetTowerWizard()->GetAttackDelay());			// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 950 + 100, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[2] < 10)
	{
		sprintf_s(upgradeInfoText, "%.2f", g_objTower[0].GetTowerWizard()->GetAttackDelay() - 0.15f); // ���� ���� ����
		TextOut(g_sfBack.dcSurface, 950 + 175, 200 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	// �ִ� ����
	UpgradeAbilityInfoPrint(400, 360, "Max Mana", 3, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);
	__PutSprite(g_sfBack.dcSurface, 415, 370, g_sfMana, 50, 50);

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	wsprintf(upgradeInfoText, "%d", maxMana);														// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 400 + 110, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[3] < 10)
	{
		wsprintf(upgradeInfoText, "%d", maxMana + 10);												// ���� ���� ����
		TextOut(g_sfBack.dcSurface, 400 + 175, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	// ���� ȸ�� �ӵ�
	UpgradeAbilityInfoPrint(675, 360, "Mana Speed", 4, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);
	__PutSprite(g_sfBack.dcSurface, 690, 370, g_sfMana, 50, 50);

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	sprintf_s(upgradeInfoText, "%.2f", manaDelay + 0.0f);											// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 675 + 100, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[4] < 10)
	{
		sprintf_s(upgradeInfoText, "%.2f", manaDelay - 0.12f);										// ���� ���� ����
		TextOut(g_sfBack.dcSurface, 675 + 175, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	// Ÿ�� �ִ� ü��
	UpgradeAbilityInfoPrint(950, 360, "Tower Max HP", 5, &g_sfBack.dcSurface, g_sfUpgradeBtn, upgradeLevel, upgradeGold);
	__PutSprite(g_sfBack.dcSurface, 965, 370, g_sfTowerIcon);

	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));
	wsprintf(upgradeInfoText, "%d", g_objTower[0].GetMaxHP());										// ���� ���� ����
	TextOut(g_sfBack.dcSurface, 950 + 100, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	if (upgradeLevel[5] < 10)
	{
		wsprintf(upgradeInfoText, "%d", g_objTower[0].GetMaxHP() + 500);							// ���� ���� ����
		TextOut(g_sfBack.dcSurface, 950 + 175, 360 + 65, upgradeInfoText, strlen(upgradeInfoText));
	}

	SelectObject(g_sfBack.dcSurface, *oldFont);
	DeleteObject(*newFont);
}

void PaintGameScreen(CTower* g_objTower, CUnitInfo* g_infoUnit, CUnitInfo* playerUnit[MAX_UNIT_COUNT], CUnitInfo* enemyUnit[MAX_UNIT_COUNT], SURFACEINFO* g_sfBG, SURFACEINFO* g_sfBtn, 
	SURFACEINFO* g_btnUnit, SURFACEINFO* g_sfMana, SURFACEINFO* g_sfRoundBtn, BOOL* buttonClick, int nBgX, int maxMana_InGame, int nowMana_InGame, int getGold, HFONT* newFont, HFONT* oldFont)
{
	__PutStretch(g_sfBack.dcSurface, nBgX, 0, MAP_SIZE_RATE, MAP_SIZE_RATE, g_sfBG);	// ���

	// Ÿ��
	g_objTower[0].GetTowerWizard()->DrawSurface(g_sfBack.dcSurface, nBgX);
	g_objTower[0].DrawSurface(g_sfBack.dcSurface, nBgX);
	g_objTower[1].DrawSurface(g_sfBack.dcSurface, nBgX);

	// ���� ���� ��ư
	SetTextColor(g_sfBack.dcSurface, RGB(0, 255, 255));
	for (int i = 0; i < UNIT_COUNT / 2; i++)
	{
		__PutSprite(g_sfBack.dcSurface, 100 + 110 * (i + 1), 350, g_sfBtn, 100, 100);	// ��ư
		__PutSprite(g_sfBack.dcSurface, 110 + 110 * (i + 1), 310, &g_btnUnit[i]);		// ���� �̹���

		__PutSprite(g_sfBack.dcSurface, 125 + 110 * (i + 1), 390, g_sfMana, 20, 20);	// �ڽ�Ʈ
		char costPrint[16];
		wsprintf(costPrint, "%d", g_infoUnit[i * 2].GetCost());
		TextOut(g_sfBack.dcSurface, 150 + 110 * (i + 1), 390, costPrint, strlen(costPrint));
		DrawGauge(g_sfBack.dcSurface, 110 + 110 * (i + 1), 420, g_infoUnit[i * 2].GetCreateDelay() - g_infoUnit[i * 2].GetCreateDelayTimer(), g_infoUnit[i * 2].GetCreateDelay());		// ���� ������ ������
	}

	// ���� ���׷��̵� ��ư
	__PutSprite(g_sfBack.dcSurface, 100, 350, g_sfBtn, 100, 100);		// ��ư
	__PutSprite(g_sfBack.dcSurface, 125, 330, g_sfMana, 50, 60);		// ���� �̹���

	__PutSprite(g_sfBack.dcSurface, 125, 400, g_sfMana, 20, 20);		// �ڽ�Ʈ
	char manaCostPrint[16];
	wsprintf(manaCostPrint, "%d", maxMana_InGame / 2);
	TextOut(g_sfBack.dcSurface, 150, 400, manaCostPrint, strlen(manaCostPrint));

	// ����
	for (int i = 0; i < MAX_UNIT_COUNT; i++)
	{
		if (playerUnit[i] != NULL)	playerUnit[i]->DrawSurface(g_sfBack.dcSurface, nBgX);
		if (enemyUnit[i] != NULL)	enemyUnit[i]->DrawSurface(g_sfBack.dcSurface, nBgX);
	}

	// ��Ʈ ����(����, ��� ���� ũ��)
	*newFont = CreateFont(25, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	SetBkMode(g_sfBack.dcSurface, TRANSPARENT);

	// ����
	SetTextColor(g_sfBack.dcSurface, RGB(0, 255, 255));
	__PutSprite(g_sfBack.dcSurface, 10, 10, g_sfMana);
	char printMana[32];
	wsprintf(printMana, "%d/%d", nowMana_InGame, maxMana_InGame);
	TextOut(g_sfBack.dcSurface, 40, 12, printMana, strlen(printMana));

	// ȹ�� ���
	SetTextColor(g_sfBack.dcSurface, RGB(200, 200, 50));
	char printGetGold[32];
	wsprintf(printGetGold, "get Gold: %d", getGold);
	TextOut(g_sfBack.dcSurface, 940, 10, printGetGold, strlen(printGetGold));

	// ��Ʈ ����(Ÿ�� ü�� ǥ��)
	SelectObject(g_sfBack.dcSurface, *oldFont);
	*newFont = CreateFont(15, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));

	// Ÿ�� ü��
	g_objTower[0].PrintTowerHP(g_sfBack.dcSurface, nBgX);
	g_objTower[1].PrintTowerHP(g_sfBack.dcSurface, nBgX);

	// �Ͻ����� ��ư
	if (buttonClick[5]) __PutSprite(g_sfBack.dcSurface, 1180, 5, &g_sfRoundBtn[3], 50, 50);
	else				__PutSprite(g_sfBack.dcSurface, 1180, 5, &g_sfRoundBtn[2], 50, 50);

	SelectObject(g_sfBack.dcSurface, *oldFont);
	DeleteObject(*newFont);
}

void PaintPauseScreen(SURFACEINFO* g_sfUpgradeBtn, SURFACEINFO* g_sfRoundBtn, BOOL* buttonClick)
{
	__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 200, MAP_HEIGHT / 2 - 100, g_sfUpgradeBtn, 400, 200);		// ��� â

	if (buttonClick[6]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 160, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[1], 100, 100);	// ����ϱ�
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 160, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[0], 100, 100);

	if (buttonClick[7]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 50, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[5], 100, 100);	// �ٽ��ϱ�
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 50, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[4], 100, 100);

	if (buttonClick[8]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 + 60, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[7], 100, 100);	// ������
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 + 60, MAP_HEIGHT / 2 - 50, &g_sfRoundBtn[6], 100, 100);
}

void PaintStageEndScreen(SURFACEINFO* g_sfUpgradeBtn, SURFACEINFO* g_sfGameResult, BOOL isWin, BOOL* buttonClick, SURFACEINFO* g_sfRectBtn, int getGold, HFONT* newFont, HFONT* oldFont)
{
	SetBkMode(g_sfBack.dcSurface, TRANSPARENT);
	SetTextColor(g_sfBack.dcSurface, RGB(0, 0, 0));

	__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 350, MAP_HEIGHT / 2 - 200, g_sfUpgradeBtn, 700, 400);			// ���� ��� â
	__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 200, MAP_HEIGHT / 2 - 150, &g_sfGameResult[isWin], 400, 100);	// ���� ��� ����

	if (buttonClick[9]) __PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 100, MAP_HEIGHT / 2 + 50, &g_sfRectBtn[1], 200, 70);		// ��������
	else				__PutSprite(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 100, MAP_HEIGHT / 2 + 50, &g_sfRectBtn[0], 200, 70);

	*newFont = CreateFont(35, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	TextOut(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - 30, MAP_HEIGHT / 2 + 70, "Next", strlen("Next"));

	// ȹ�� ��� ���
	SetTextColor(g_sfBack.dcSurface, RGB(200, 200, 50));
	*newFont = CreateFont(25, 0, 0, 0, FW_HEAVY, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
	*oldFont = (HFONT)SelectObject(g_sfBack.dcSurface, *newFont);
	char printGetGoldResult[32];
	wsprintf(printGetGoldResult, "Get Gold: %d", getGold);
	TextOut(g_sfBack.dcSurface, WINDOW_WIDTH / 2 - strlen(printGetGoldResult) * 7, 250, printGetGoldResult, strlen(printGetGoldResult));

	SelectObject(g_sfBack.dcSurface, *oldFont);
	DeleteObject(*newFont);
}

// ���� ���׷��̵� ����
void UpgradeUnitInfoPrint(CUnitInfo& unitInfo, int x, int y, HDC* backDcSurface, SURFACEINFO* g_sfUpgradeBtn)
{
	__PutSprite(*backDcSurface, x, y, g_sfUpgradeBtn, 250, 140);
	__PutSprite(*backDcSurface, x + 15, y + 10, &unitInfo.GetpSfUnit()[0]);

	char upgradeInfoText[32];
	SetTextColor(*backDcSurface, RGB(0, 0, 0));

	// ���� ����
	TextOut(*backDcSurface, x + 90, y + 10, "hp", strlen("hp"));					// ü��
	wsprintf(upgradeInfoText, "%d", unitInfo.GetMaxHP());
	TextOut(*backDcSurface, x + 145, y + 10, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 25, "attack", strlen("attack"));			// ���ݷ�
	wsprintf(upgradeInfoText, "%d", unitInfo.GetAttackDamage());
	TextOut(*backDcSurface, x + 145, y + 25, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 40, "attSpe", strlen("attSpe"));			// ���� ������
	sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetAttackDelay());
	TextOut(*backDcSurface, x + 145, y + 40, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 55, "create", strlen("create"));			// ���� ������
	sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetCreateDelay());
	TextOut(*backDcSurface, x + 145, y + 55, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 70, "speed", strlen("speed"));				// �̵��ӵ�
	wsprintf(upgradeInfoText, "%d", unitInfo.GetMoveSpeed());
	TextOut(*backDcSurface, x + 145, y + 70, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 85, "range", strlen("range"));				// ���� ��Ÿ�
	wsprintf(upgradeInfoText, "%d", unitInfo.GetAttackRange());
	TextOut(*backDcSurface, x + 145, y + 85, upgradeInfoText, strlen(upgradeInfoText));

	TextOut(*backDcSurface, x + 90, y + 100, "dmg", strlen("dmg"));					// �ڽ�Ʈ
	wsprintf(upgradeInfoText, "%d", unitInfo.GetCost());
	TextOut(*backDcSurface, x + 145, y + 100, upgradeInfoText, strlen(upgradeInfoText));

	// ���� ����
	if (unitInfo.GetLevel() < 20)
	{
		if (unitInfo.GetLevel() % 5 == 4)
		{
			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetMaxHP() * 1.1f * 1.1f));			// ü��
			TextOut(*backDcSurface, x + 200, y + 10, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetAttackDamage() * 1.1f * 1.1f));	// ���ݷ�
			TextOut(*backDcSurface, x + 200, y + 25, upgradeInfoText, strlen(upgradeInfoText));

			sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetAttackDelay() * 0.95f * 0.95f);		// ���� ������
			TextOut(*backDcSurface, x + 200, y + 40, upgradeInfoText, strlen(upgradeInfoText));

			sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetCreateDelay() * 0.95f * 0.95f);		// ���� ������
			TextOut(*backDcSurface, x + 200, y + 55, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetMoveSpeed() + 1));				// �̵��ӵ�
			TextOut(*backDcSurface, x + 200, y + 70, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetAttackRange() * 1.2f));			// ���� ��Ÿ�
			TextOut(*backDcSurface, x + 200, y + 85, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetCost() + 2));						// �ڽ�Ʈ
			TextOut(*backDcSurface, x + 200, y + 100, upgradeInfoText, strlen(upgradeInfoText));
		}
		else
		{
			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetMaxHP() * 1.1f));					// ü��
			TextOut(*backDcSurface, x + 200, y + 10, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetAttackDamage() * 1.1f));			// ���ݷ�
			TextOut(*backDcSurface, x + 200, y + 25, upgradeInfoText, strlen(upgradeInfoText));

			sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetAttackDelay() * 0.95f);				// ���� ������
			TextOut(*backDcSurface, x + 200, y + 40, upgradeInfoText, strlen(upgradeInfoText));

			sprintf_s(upgradeInfoText, "%.2f", unitInfo.GetCreateDelay() * 0.95f);				// ���� ������
			TextOut(*backDcSurface, x + 200, y + 55, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetMoveSpeed()));					// �̵��ӵ�
			TextOut(*backDcSurface, x + 200, y + 70, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetAttackRange()));					// ���� ��Ÿ�
			TextOut(*backDcSurface, x + 200, y + 85, upgradeInfoText, strlen(upgradeInfoText));

			wsprintf(upgradeInfoText, "%d", (int)(unitInfo.GetCost()));							// �ڽ�Ʈ
			TextOut(*backDcSurface, x + 200, y + 100, upgradeInfoText, strlen(upgradeInfoText));
		}
	}

	TextOut(*backDcSurface, x + 180, y + 55, "->", strlen("->"));

	wsprintf(upgradeInfoText, "Lv.%d / 20", unitInfo.GetLevel());	// ����
	TextOut(*backDcSurface, x + 15, y + 80, upgradeInfoText, strlen(upgradeInfoText));

	SetTextColor(*backDcSurface, RGB(200, 200, 50));							// ���׷��̵� ���
	wsprintf(upgradeInfoText, "%d Gold", unitInfo.GetLevelUpGold());
	TextOut(*backDcSurface, x + 15, y + 100, upgradeInfoText, strlen(upgradeInfoText));
}

// ������, ����, Ÿ�� ���׷��̵� ����
void UpgradeAbilityInfoPrint(int x, int y, char* upgradeName, int abilityNum, HDC* backDcSurface, SURFACEINFO* g_sfUpgradeBtn, int* upgradeLevel, int* upgradeGold)
{
	__PutSprite(*backDcSurface, x, y, g_sfUpgradeBtn, 250, 140);

	SetTextColor(*backDcSurface, RGB(0, 0, 0));
	TextOut(*backDcSurface, x + 105, y + 35, upgradeName, strlen(upgradeName));			// ���׷��̵� �̸�
	TextOut(*backDcSurface, x + 145, y + 65, "->", strlen("->"));

	char upgradeInfoText[32];
	wsprintf(upgradeInfoText, "Lv.%d / 10", upgradeLevel[abilityNum]);		// ����
	TextOut(*backDcSurface, x + 15, y + 80, upgradeInfoText, strlen(upgradeInfoText));

	SetTextColor(*backDcSurface, RGB(200, 200, 50));			// ���׷��̵� ���
	wsprintf(upgradeInfoText, "%d Gold", upgradeGold[abilityNum]);
	TextOut(*backDcSurface, x + 15, y + 100, upgradeInfoText, strlen(upgradeInfoText));
}

// �ڽ� ���� ���� ������ ������
void DrawGauge(HDC hdc, int x, int y, float currentValue, float maxValue)
{
	if (maxValue <= 0)	return;			// maxValue�� 0 ������ ��� ����
	float fillRatio = currentValue / maxValue;
	if (fillRatio < 0)	fillRatio = 0;  // �ּ� 0
	if (fillRatio > 1)	fillRatio = 1;  // �ִ� 1

	Rectangle(hdc, x, y, x + BAR_WIDTH, y + BAR_HEIGHT);	// ������ ��� (ȸ��)

	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));		// ä���� ������ (�Ķ���)
	RECT fillRect = { x, y, x + (BAR_WIDTH * fillRatio), y + BAR_HEIGHT };
	FillRect(hdc, &fillRect, hBrush);

	DeleteObject(hBrush);
}