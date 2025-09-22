#ifndef __DEFINEDATA_H__
#define __DEFINEDATA_H__

#include <Windows.h>

#define UNIT_COUNT		6
#define UNIT_SF_COUNT	5

#define XSPEED_JUMP 7		// �̵� �ӵ�
#define XSPEED_WALK 10
#define YSPEED_JUMP -20
#define GRAVITY		1.0

#define MAX_YPOS 300		// �Ѱ� �̵� �ݰ�
#define MAX_XPOS 500
#define MIN_XPOS 100

#define MAP_SIZE_RATE	5
#define UNIT_SIZE_RATE	3
#define MAP_WIDTH		500*MAP_SIZE_RATE
#define MAP_HEIGHT		110*MAP_SIZE_RATE
#define WINDOW_WIDTH	500*2.5

#define MAX_UNIT_COUNT	50
#define FIREBALL_MAX	64

#define UNIT_MAX_LEVEL		20
#define ABILITY_MAX_LEVEL	10

#define PI 3.141592

#define BAR_WIDTH 80	// ������ ����
#define BAR_HEIGHT 15   // ������ ����

#define STARTGOLD 100000	// �׽�Ʈ�� �ݾ�

typedef struct SURFACEINFOtag
{
	HDC			dcSurface;		// ��Ʈ���� ������ִ� ǥ�� DC
	HBITMAP		hBmp;			// ��Ʈ�� �ڵ�
	HBITMAP		hOldBmp;		// ���� ��Ʈ�� �ڵ� ( dc ������ ���� )
	int			nTop;
	int			nLeft;
	int			nWidth;
	int			nHeight;
	COLORREF	crColorKey;		// �÷�Ű
} SURFACEINFO;

enum Screen
{
	titleScreen = 0,	// �̾��ϱ�, ���ν���, ����
	readyScreen,		// ���� �������� �����ֱ�, ���� ����, ���� �ǹ� �ɷ� ���׷��̵�
	gameScreen,			// ���� ȭ��
	pauseScreen,		// �Ͻ����� â
	stageEndScreen		// ���� ��� â
};

#endif