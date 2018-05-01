#pragma once
#include "gameNode.h"
enum ELEVELAVTIVE { ELEVELAVTIVE_NONE, ELEVELAVTIVE_EASY, ELEVELAVTIVE_NORMAL, ELEVELAVTIVE_HARD, ELEVELAVTIVE_BACK};
class levelScene : public gameNode
{
private:
	ELEVELAVTIVE state;
	ELEVELAVTIVE excute;

	D2D1_RECT_F easy;
	D2D1_RECT_F normal;
	D2D1_RECT_F hard;
	D2D1_RECT_F back;
public:
	levelScene();
	~levelScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};