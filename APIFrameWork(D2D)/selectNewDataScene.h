#pragma once
#include "gameNode.h"
class selectNewDataScene : public gameNode
{
private:
	ESELECTACTIVE active;
	ESELECTACTIVE excute;
	sSaveData dataFile[3];
	sViewData data[3];
public:
	selectNewDataScene();
	~selectNewDataScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};