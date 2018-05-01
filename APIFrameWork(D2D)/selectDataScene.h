#pragma once
#include "gameNode.h"
class selectDataScene : public gameNode
{
private:
	ESELECTACTIVE active;
	ESELECTACTIVE excute;
	sSaveData dataFile[3];
	sViewData data[3];
public:
	selectDataScene();
	~selectDataScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};