#pragma once
#include "gameNode.h"
enum ESOUNDACTION {ESOUNDACTION_NONE, ESOUNDACTION_BGM, ESOUNDACTION_EFFECT, ESOUNDACTION_BACK};
class soundScene : public gameNode
{
private:
	ESOUNDACTION state;
	ESOUNDACTION action;

	D2D1_RECT_F bgmRect;
	D2D1_RECT_F effectRect;
	D2D1_RECT_F back;

public:
	soundScene();
	~soundScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};