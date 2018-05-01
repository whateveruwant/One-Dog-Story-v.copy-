#pragma once
#include "gameNode.h"
#include "Map.h"
class mainGameAgainScene : public gameNode
{
private:
	Map* map;

	bool popUp;
	EPOPUPACTIVE state;
	EPOPUPACTIVE excute;

	D2D1_RECT_F bBack;
	D2D1_RECT_F bLoad;
	D2D1_RECT_F bOut;
public:
	mainGameAgainScene();
	~mainGameAgainScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void popupInit();
	void popupUpdate();
	void popupRender();
};