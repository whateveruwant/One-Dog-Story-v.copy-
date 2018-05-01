#pragma once
#include "gameNode.h"
#include "singletonBase.h"

class cameraManager :public singletonBase<cameraManager>
{
private:
	D2D_POINT_2F* _standard;
	EViEWDIRECTION* _direction;

	D2D_POINT_2F _current;
	float speed;

	bool bossMode;
	float vibeTime;

	tchar TextStr[100];
	bool textMode;
	float textTime;

	ID2D1SolidColorBrush* black;
	float alpha;
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	D2D_POINT_2F getAbsPosition(const D2D_POINT_2F _pt);

	void setPositionMemotyRick(D2D_POINT_2F* _pt) { _standard = _pt; _current = *_standard; }
	void setDirectionMemotyRick(EViEWDIRECTION* _dr) { _direction = _dr; }

	D2D_POINT_2F getStandardPoint() { return *_standard; }

	void drawCamera();

	void setCameraCenter() {
		_current.x = _standard->x;
		_current.y = _standard->y;
	}

	void setBossMode(bool mode) { bossMode = mode; }
	void textOut(tstring str);
	void setVibeMode();
	void setStart() { alpha = 1.0f; }
};