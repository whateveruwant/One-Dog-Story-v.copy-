#pragma once
#include "gameNode.h"
#include "invenItem.h"	
struct SDOOR {
	float x, y; //¸Ê¿¡ ´ëÇÑ ÁÂÇ¥
	EDOORKIND kind;
	tchar destination[50];		//¸ñÀû¸Ê
	float dsX, dsY;				//¸ñÀû¸ÊÀÇ ÁÂÇ¥
};

struct SDOGINFO {
	D2D_RECT_F* dogRect;
	vector<EINVENITEM>* dogInvetory;
};

class Door : public gameNode
{
private:
	SDOOR info;
	D2D_RECT_F rect;
	SDOGINFO dogInfo;

	bool active;
	bool canOpen;
	bool opening;
	bool goChangeMap;

public:
	Door();
	~Door();
	
	HRESULT init(SDOOR _door, tstring MapName);
	void release(void);
	void update(void);
	void render(void);

	void setMemoryDogRect(D2D_RECT_F& Rect) { dogInfo.dogRect = &Rect; }
	void setMemoryDogInven(vector<EINVENITEM>& Invetory) { dogInfo.dogInvetory = &Invetory; }

	void GoChangeMap();
	void getActive();
	void checkCanOpen();

	bool getisOpening() { return opening; }
	bool getGoChangeMap() { return goChangeMap; }
	tstring getChangeMapName() { return info.destination; }
	D2D1_POINT_2F getChangePosition() { return { info.dsX, info.dsY }; }
};