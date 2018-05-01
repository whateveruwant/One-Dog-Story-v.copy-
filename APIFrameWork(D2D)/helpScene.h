#pragma once
#include "gameNode.h"
class helpScene : public gameNode
{
private:
	EHELPACTIVEMENU activeMenu;
	EHELPEXCUTEMENU excuteMenu;

	bool onBack;
	bool goBack;

public:
	helpScene();
	~helpScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};