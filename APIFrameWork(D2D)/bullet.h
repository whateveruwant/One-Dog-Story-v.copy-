#pragma once
#include "gameNode.h"
#include "dog.h"
struct SBULLET {
	D2D1_POINT_2F position;
	float angle;
	float time;
	float gravity;
	float speedx;
};
class bullet : public gameNode
{
private:
	D2D_RECT_F* clubRect;
	SDOGWEAPONINFO* dogWeaponInfo;
	dog* dogInfo;

	vector<SBULLET> vGunBullet;
	vector<SBULLET> vShotGunBullet;
	vector<SBULLET> vRocketBullet;
	vector<SBULLET> vPlasmaBullet;

	vector<D2D_RECT_F*> somethings;
	vector<bool*> isAttacks;
	vector<int*> vAtkNum;
	vector<bool*> isDelets;

	int frameX;
	int count;


public:
	bullet();
	~bullet();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setClubRect(D2D_RECT_F* _clubRect) {
		clubRect = _clubRect;
	}
	void setDogWeaponMemory(SDOGWEAPONINFO* _dogWeaponInfo) {
		dogWeaponInfo = _dogWeaponInfo;
	}
	void setDogMemory(dog* _dogInfo) { dogInfo = _dogInfo; }

	void addTheSomeThings(D2D_RECT_F* rect, bool* isAttack, bool* isDelete, int* AtkNum) {
		somethings.push_back(rect);
		isAttacks.push_back(isAttack);
		isDelets.push_back(isDelete);
		vAtkNum.push_back(AtkNum);
	}
	void deleteSomeThings(D2D_RECT_F* rect, bool* isAttack, bool* isDelete, int* AtkNum) {
		vector<D2D_RECT_F*>::iterator tmpRectiter = somethings.begin();
		vector<bool*>::iterator tmpIter = isAttacks.begin();
		vector<bool*>::iterator tmpIter2 = isDelets.begin();
		vector<int*>::iterator tmpIter3 = vAtkNum.begin();
		for (int i = 0; i < somethings.size(); ++i) {
			if (somethings.at(i) == rect) {
				tmpRectiter += i;
				tmpIter += i;
				tmpIter2 += i;
				tmpIter3 += i;
				somethings.erase(tmpRectiter);
				isAttacks.erase(tmpIter);
				isDelets.erase(tmpIter2);
				vAtkNum.erase(tmpIter3);
			}
		}
	}

	void collisionBullet();
	void pleaseDelete();

	void createBullet();
	void moveBullet();
};

