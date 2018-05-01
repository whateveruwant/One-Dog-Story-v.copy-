#pragma once
#include "gameNode.h"
class CollisionManager : public gameNode
{
private:
	D2D_RECT_F leftToRightArm;
	D2D_RECT_F headToBottom;
	D2D_RECT_F body;
	D2D_POINT_2F* charPo;
	float charWidth;
	float charHeight;
	bool onView;

	SCOLLILINE line[LINEMAX];
	int lineNum;
	SCOLLIRECT rect[RECTMAX];
	int rectNum;

	vector<D2D1_RECT_F*> vObjectRect;

	tstring currentMapName;
public:
	CollisionManager();
	~CollisionManager();

	HRESULT init(D2D_POINT_2F* posi, float width, float height, tstring mapName);
	void release(void);
	void update(tstring mapName);
	void render(void);

	D2D_RECT_F* getBody() { return &body; }
	D2D_RECT_F* getHeadToBottom() { return &headToBottom; }
	D2D_RECT_F* getLeftToRightArm() { return &leftToRightArm; }

	void updateRectPosi();

	bool checkCollisionLeft();
	bool checkCollisionRight();
	bool checkCollisionTop();
	float checkCollisionBottom();
	bool checkCollisionHill();

	float checkUserCollision(D2D_RECT_F rect);

	void load(tstring mapName);
	void addObjectRect(D2D1_RECT_F* rect) { vObjectRect.push_back(rect); }
	void deleteObjectRect(D2D1_RECT_F* rect) {
		for (int i = 0; i < vObjectRect.size(); ++i) {
			if (rect == vObjectRect.at(i)) {
				vector<D2D1_RECT_F*>::iterator tmpIter = vObjectRect.begin();
				tmpIter += i;
				vObjectRect.erase(tmpIter);
			}
		}
	}
};