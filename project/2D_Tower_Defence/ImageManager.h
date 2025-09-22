#ifndef __IMAGEMANAGER_H__
#define __IMAGEMANAGER_H__

#include "DefineData.h"
#include "CUnitInfo.h"
#include "CTower.h"

BOOL __CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);	// dcScreen�� ȣȯ�Ǵ� �ĸ�ǥ��DC ����
void __LoadSurface(HDC dcScreen, SURFACEINFO* psInfo, int nLeft, int nTop);				// ǥ�� ���� �� �ε�,  ���� ������Ʈ �Ǵ� ��Ʈ�� DC ���� �� ��Ʈ�� �ε�
void __ReleaseSurface(SURFACEINFO* psInfo);							// ������ ǥ�� ����

BOOL __PutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);		// �̹��� ���
BOOL __PutStretch(HDC dcDst, int x, int y, int xRate, int yRate, SURFACEINFO* psInfo);
BOOL __PutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo);		// ��������Ʈ
BOOL __PutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int width, int height);	// ��������Ʈ
BOOL __CompleteBlt(HDC dcScreen, SURFACEINFO* psInfo);				// dcScreen�� ǥ���� ���� ( �ĸ�ǥ�� -> ȭ��DC )
HBITMAP __MakeDDBFromDIB(HDC hdc, char* Path);						// DIB -> DDB�� ��ȯ

void __SetImgSurface(SURFACEINFO* psfInfo);							// SURFACEINFO �̹��� �ʱ�ȭ
void __SetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey);	// SURFACEINFO ��������Ʈ �ʱ�ȭ

void __Init(HDC dcScreen, SURFACEINFO& g_sfBack, SURFACEINFO& g_sfBG, CUnitInfo g_infoUnit[UNIT_COUNT], SURFACEINFO g_btnUnit[UNIT_COUNT / 2], 
	SURFACEINFO& g_btn, CTower g_objTower[2], SURFACEINFO& g_sfTitle, SURFACEINFO& g_sfUpgradeBtn, SURFACEINFO g_sfGameResult[2], 
	SURFACEINFO& g_sfMana, SURFACEINFO& g_sfGold, SURFACEINFO& g_sfTowerIcon, SURFACEINFO g_sfUpgradeArrow[2], SURFACEINFO& g_sfBtnScreen,
	SURFACEINFO g_sfRoundBtn[8], SURFACEINFO g_sfRectBtn[4], SURFACEINFO g_sfArrow[2]);	// �ϰ� ǥ�� ���� 
void __DestroyAll(SURFACEINFO& g_sfBack, SURFACEINFO& g_sfBG, CUnitInfo	g_infoUnit[UNIT_COUNT], CUnitInfo** g_objPlayerUnit, CUnitInfo** g_objEnemyUnit);			// �ϰ� ǥ�� �ı�
void __DestroyUnit(CUnitInfo** g_objPlayerUnit, CUnitInfo** g_objEnemyUnit);
void DeleteUnit(CUnitInfo** g_objPlayerUnit, CUnitInfo** g_objEnemyUnit);

#endif