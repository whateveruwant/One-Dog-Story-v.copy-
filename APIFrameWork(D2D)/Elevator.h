#pragma once
#include "gameNode.h"
#include "dog.h"
class Elevator : public gameNode
{
private:
	SELEVATOR info;
	image liftImage;
	vector<D2D1_RECT_F> switchRect;
	D2D_POINT_2F liftPosition;
	D2D1_RECT_F liftRect;

	bool onLift;
	bool isTouchSwitch;
	int touchSwitch;
	bool startToEnd;

	dog* dogMemory;

public:
	Elevator();
	~Elevator();

	HRESULT init(SELEVATOR _Elevator, tstring MapName);
	void release(void);
	void update(void);
	void render(void);

	void moveElevator();
	void setMemoryDog(dog* _dog) { dogMemory = _dog; }
	D2D1_RECT_F& getRect() { return liftRect; }
	bool getOnLift() { return onLift; }
	EELEVATORKIND getKind() { return info.kind; }
	void deleteRect();
};