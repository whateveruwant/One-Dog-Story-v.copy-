#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "CollisionManager.h"
enum EENEMYACTKIND { EENEMYACTKIND_STOP, EENEMYACTKIND_MOVE, EENEMYACTKIND_ATTACK, EENEMYACTKIND_DEATH};
class Enemy : public gameNode
{
protected:
	CollisionManager* boxs;

	animation* aniIDLE;
	animation* aniDEAD;
	animation* aniMOVE;

	SENEMY info;
	D2D1_RECT_F rect;
	D2D1_POINT_2F position;
	int currentHP;
	float speed;
	tstring imageName;
	D2D1_POINT_2F* dogPosition;
	float gravity;
	EENEMYACTKIND action;
	bool _isFollow;
	bool _isLeft;
	bool _isDamage;
	int damageNum;
	bool _isDelete;
	bool _isAir;

	float orderBuffer;
	bool create;
public:
	Enemy() {}
	~Enemy() {}

	//상호참조를 위한 함수
	tstring getName() { return imageName; }
	void setDogPositionMemory(D2D1_POINT_2F* _dogPosition) { dogPosition = _dogPosition; }
	D2D1_RECT_F* getRectMemory() { return &rect; }
	bool* getIsAttackMemory() { return &_isDamage; }
	bool* getIsDeleteMemory() { return &_isDelete; }
	EENEMYACTKIND* getAction() { return &action; }
	bool* getCreate() { return &create; }
	D2D1_POINT_2F getPosition() { return position; }
	int* getDamageMemory() { return &damageNum; }

	//기본상속함수
	HRESULT init(SENEMY _info, tstring _mapName);
	void release(void);
	void update(tstring mapName);
	void render(void);

	//부수적인 행동을 위한 함수
	void actionOrder();
	void move();
	void Fall();
};
struct EBOSSBULLET {
	D2D1_POINT_2F point;
	D2D1_RECT_F rect;
};
enum EBOSSACTION { EBOSSACTION_IDLE, EBOSSACTION_FIRE, EBOSSACTION_DEAD};
class Enemy_BOSS : public Enemy
{
private:
	int frameX;
	int count;
	EBOSSACTION action;

	progressBar* hpBar;
	int maxHP;
	float bulletBlankTime;
	vector<EBOSSBULLET> vBullet;
	vector<EBOSSBULLET>::iterator viBullet;
	
	float deadPoint;
public:
	Enemy_BOSS() {}
	~Enemy_BOSS() {}

	//기본상속함수
	HRESULT init(SENEMY _info, tstring _mapName);
	void release(void);
	void update(tstring mapName);
	void render(void);

	vector<EBOSSBULLET>* getBossBullet() { return &vBullet; }

	void fireBullet();
	void move();
	void moveBullet();
};