#pragma once
#include "gameNode.h"
class DropItem : public gameNode
{
protected:
	SDropItem info;
	D2D1_POINT_2F* dogPo;

public:
	DropItem() {}
	~DropItem() {}

	HRESULT init(EDROPITEM _kind, float x, float y);
	void release(void);
	void update(void);
	void render(void);

	void setDogPosition(D2D_POINT_2F& Point) { dogPo = &Point; }
	D2D_POINT_2F getPoint() { return { info.x, info.y}; }
	EDROPITEM getKind() { return info._kind; }
};