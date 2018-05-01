#pragma once
#include "image.h"
#include "invenItem.h"
#define LINEMAX 300
#define DOORMAX 15
#define RECTMAX 50
#define ELEVATORMAX 20
#define OBJECTMAX 500
#define DOGVIEW_X WINSIZEX_NUM/2
#define DOGVIEW_Y WINSIZEY_NUM/2 + 50
#define UPGRADEMAX 15
#define ENEMYMAX 100
enum EHELPACTIVEMENU { EHELPACTIVEMENU_NONE, EHELPACTIVEMENU_JUMP, EHELPACTIVEMENU_LEFT, EHELPACTIVEMENU_RIGHT, EHELPACTIVEMENU_UP, EHELPACTIVEMENU_DOWN, EHELPACTIVEMENU_USE, EHELPACTIVEMENU_MOVEBOX, EHELPACTIVEMENU_ATTACK, EHELPACTIVEMENU_FINDING, EHELPACTIVEMENU_NEXT, EHELPACTIVEMENU_BEFORE, EHELPACTIVEMENU_JETPACK, EHELPACTIVEMENU_GOBACK, EHELPACTIVEMENU_SOUND
};
enum EHELPEXCUTEMENU { EHELPEXCUTEMENU_NONE, EHELPEXCUTEMENU_JUMP, EHELPEXCUTEMENU_LEFT, EHELPEXCUTEMENU_RIGHT, EHELPEXCUTEMENU_UP, EHELPEXCUTEMENU_DOWN, EHELPEXCUTEMENU_USE, EHELPEXCUTEMENU_MOVEBOX, EHELPEXCUTEMENU_ATTACK, EHELPEXCUTEMENU_FINDING, EHELPEXCUTEMENU_NEXT, EHELPEXCUTEMENU_BEFORE, EHELPEXCUTEMENU_JETPACK, EHELPEXCUTEMENU_GOBACK, EHELPEXCUTEMENU_SOUND
};
enum EPOPUPACTIVE { EPOPUPACTIVE_NONE, EPOPUPACTIVE_BACK, EPOPUPACTIVE_LOAD, EPOPUPACTIVE_OUT};
enum EINVENITEM { EINVENITEN_NONE, EINVENITEN_BOOTS, EINVENITEN_CARD_RED, EINVENITEN_CARD_GREEN, EINVENITEN_CARD_BLUE, EINVENITEN_CARD_WHITE, EINVENITEN_CARD_USE };
enum EDROPITEM { EDROPITEM_NONE, EDROPITEM_HEAL, EDROPITEM_MONEY, EDROPITEM_BULLET };
enum EWEAPON { EWEAPON_NONE, EWEAPON_CLUP, EWEAPON_GUN, EWEAPON_SHOTGUN, EWEAPON_ROCKET, EWEAPON_PLASMA };
enum EOBJECTKIND { EOBJECTKIND_NONE, EOBJECTKIND_MADE };
enum EELEVATORKIND { EELEVATORKIND_SMALL, EELEVATORKIND_LASER };
enum EDOORKIND { EDOORKIND_NONE, EDOORKIND_BREAK, EDOORKIND_FREE, EDOORKIND_NEED_RED, EDOORKIND_NEED_BLUE, EDOORKIND_NEED_GREEN, EDOORKIND_NEED_WHITE, EDOORKIND_NEED_OBJECT };
enum EMAKELINE { EMAKELINE_NONE, EMAKELINE_HALF, EMAKELINE_DONE };
enum EMAKERECT { EMAKERECT_NONE, EMAKERECT_ONEPOINT, EMAKERECT_DONE };
enum EMAKEELEVATOR { EMAKEELEVATOR_NONE, EMAKEELEVATOR_STARTSET, EMAKEELEVATOR_ENDSET, EMAKEELEVATOR_SWITCHSET1, EMAKEELEVATOR_SWITCHSET2};
enum EJUMPSTATE { EJUMPSTATE_NONE, EJUMPSTATE_READY, EJUMPSTATE_UPING, EJUMPSTATE_DOWNING, EJUMPSTATE_END };
enum EViEWDIRECTION { EViEWDIRECTION_LEFT, EViEWDIRECTION_RIGHT, EViEWDIRECTION_UP, EViEWDIRECTION_DOWN };
enum EENEMYKIND { EENEMYKIND_NONE, EENEMYKIND_MADE };
struct sViewData {
	bool _isExist;
};
enum ESELECTACTIVE { ESELECTACTIVE_NONE, ESELECTACTIVE_DATA1, ESELECTACTIVE_DATA2, ESELECTACTIVE_DATA3, ESELECTACTIVE_BACK };
struct SDropItem {
	EDROPITEM _kind;
	float x, y;
};
struct SWEAPON {
	EWEAPON kind;
	tstring name;
	int upgrade;
	int bulletMax;
	int bulletNum;
};
struct SDOGWEAPONINFO {
	SWEAPON aWeapon[6];
	int currentWeapon;
};
struct SCOLLILINE {
	D2D_POINT_2F postPoint;
	D2D_POINT_2F endPoint;
	EMAKELINE state;
};
struct SCOLLIRECT {
	D2D_RECT_F rect;
	EMAKERECT state;
};
struct SOBJECT {
	float x, y; //�ʿ� ���� ��ǥ
	EOBJECTKIND kind;
	tchar name[50];
};
struct SELEVATOR {
	float startX, startY;	//������
	float endX, endY;		//����
	EELEVATORKIND kind;
	EMAKEELEVATOR state;
	tchar name[50];
	D2D_POINT_2F switchPosition[2]; //����ġ��ǥ
};
struct SENEMY {
	float x, y; //�ʿ� ���� ��ǥ
	EENEMYKIND kind;
	tchar name[50];
};
struct sSaveData {
	tchar mapName[50];
	D2D_POINT_2F Position;
	EINVENITEM inventory[9];
	int bulletMax[6];
	int bulletNum[6];
	int upgrade[6];
	int currentWeapon;
	int maxHP;
	int currentHP;
	int money;
	int addSpeed;
	tchar time[50];
};
class gameNode
{
private:
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};