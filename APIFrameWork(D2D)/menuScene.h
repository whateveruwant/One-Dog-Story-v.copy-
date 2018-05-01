#pragma once
#include "gameNode.h"
enum EMENUDOWN { EMENUDOWN_NONE, EMENUDOWN_NEWGAME, EMENUDOWN_CONTINUE, EMENUDOWN_HELP, EMENUDOWN_EXIT};
enum EMENUUP { EMENUUP_NONE, EMENUUP_NEWGAME, EMENUUP_CONTINUE, EMENUUP_HELP, EMENUUP_EXIT };
class menuScene : public gameNode
{
private:
	EMENUDOWN state;
	EMENUUP excute;

public:
	menuScene();
	~menuScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void clickMouse();
	void buttonRender();
};