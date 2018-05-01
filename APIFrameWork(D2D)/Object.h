#pragma once
#include "gameNode.h"
#include "invenItem.h"
#include "dog.h"
#include "DropItem.h"

//오브젝트
class Object : public gameNode
{
protected:
	D2D1_POINT_2F	position;
	D2D_RECT_F		rect;
	tstring			imageName;

	D2D_POINT_2F*	dogPo;
	D2D_RECT_F*		dogRect;
	bool			isTouch;

	float time;
	dog* dogMemory;
public:
	Object();
	~Object();

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);

	bool getIsTouch() { return isTouch; }

	D2D1_POINT_2F getPoint() {return position;}
	tstring getImageName() { return imageName; }
	void setMemoryDog(dog* _dog) { dogMemory = _dog; }
	void setMemoryDogRect(D2D_RECT_F& Rect) { dogRect = &Rect; }
	void setMemoryDogPoint(D2D_POINT_2F& Point) { dogPo = &Point; }
	void setTime(float num) { time = num; }
	int getTime() { return (int)time; }

	D2D1_RECT_F& getRect() { return rect; }
	void deleteRect();
};

//////////////////////////////////////////////////////////////////
// 자식 오브젝트 클래스
//////////////////////////////////////////////////////////////////

class Object_TOOL : public Object
{
private:
	vector<EINVENITEM>* dogInvetory;
	bool isOpen;

public :
	Object_TOOL() {}
	~Object_TOOL() {}

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);

	void setMemoryDogInven(vector<EINVENITEM>& Invetory) { dogInvetory = &Invetory; }
};

class Object_BOX : public Object
{
private:
	EDROPITEM dropItem[3];
	bool isBreak;
	int damageNum; //실제로 사용하지는 않을꺼임
	bool pleaseDelete;
	vector<DropItem*>* vDropsItem;
	float alpha;

public:
	Object_BOX() {}
	~Object_BOX() {}

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);
	void ifBreak();

	int* getDamageMemory() { return &damageNum; }
	bool* getBoolMemory() { return &isBreak; }
	bool* getDeleteMemory() { return &pleaseDelete; }
	void setvDropItem(vector<DropItem*>* _vDropsItem) {
		vDropsItem = _vDropsItem;
	}
};

class Object_DAMAGE : public Object
{
private:
	EDROPITEM dropItem;
	D2D_RECT_F damageRect;
	float roopTime;
	bool isRoop;

	int count;
	int frame;


public:
	Object_DAMAGE() {}
	~Object_DAMAGE() {}

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);
};

class Object_ITEM : public Object
{
private:
	bool _isUse;
public:
	Object_ITEM() {}
	~Object_ITEM() {}

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);

	bool getIsUse() { return _isUse; }
};

class Object_VENDING : public Object
{
public:
	Object_VENDING() {}
	~Object_VENDING() {}

	HRESULT init(SOBJECT info, tstring MapName);
	void release(void);
	void update(void);
	void render(void);
};