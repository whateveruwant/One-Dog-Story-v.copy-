#pragma once
#include "gameNode.h"
#include "invenItem.h"
#include "CollisionManager.h"

class dog : public gameNode
{
private:
	CollisionManager* boxs;
	D2D_POINT_2F dogPo;
	//D2D_POINT_2F jumpPo;
	//bool setjumpPo;

	vector<EINVENITEM> inventory;
	SDOGWEAPONINFO weaponInfo;

	bool _isDead;
	int maxHP;
	int currentHP;
	int money;
	float speed, jumppower;
	float gravity;

	EJUMPSTATE jumpstate;
	EViEWDIRECTION viewDirection;

	int addSpeed;
	bool _isAttack;
	bool _isLeft;
	bool _inAir;
	bool _isJump;
	bool _isMove;
	bool _isHill;
	bool _haveBoots;
	bool _bootsJump;
	bool _isTrans;
	float transTime;

	D2D_RECT_F damageRect;
	tstring _mapName;
public:
	dog();
	~dog();

	HRESULT init(tstring mapName);
	void release(void);
	void update(tstring mapName);
	void render(void);

	void initForWeapon();

	void move();
	void isAir();
	void jump();
	void fall();
	void hill();
	void attack();

	void swapWeapon();
	void setTrans(float time) {
		_isTrans = true;
		transTime = TIMEMANAGER->getWorldTime() + time;
	}
	void damage(int damage) { 
		if (!_isTrans) {
			currentHP -= damage;
			SOUNDMANAGER->play("Dogdamage", 1.0f * effectSound);
			setTrans(1);
		}
		if (currentHP <= 0) {
			currentHP = 0;
		}
		if (currentHP <= 0 && !_isDead) {
			_isDead = true;
			ANIMATIONMANAGER->start(L"dog_die");
		}
	}

	void whereView();
	void movePosition(D2D_POINT_2F po) { dogPo = po; boxs->updateRectPosi(); CAMERAMANAGER->setCameraCenter(); }
	void compulsionJump() {
		_isJump = true;
		_isHill = false;
		jumpstate = EJUMPSTATE_UPING;
		ANIMATIONMANAGER->start(L"jumpEffect");
		ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing");
	}
	void modifyX(float x) { if(!boxs->checkCollisionLeft()) { dogPo.x += x; } boxs->updateRectPosi(); }
	void modifyY(float y) { dogPo.y += y;}
	D2D_RECT_F* getRectMemory() { return boxs->getBody(); }
	vector<EINVENITEM>* getInvenMemory() { return &inventory; }
	SDOGWEAPONINFO* getWeaponMemory() { return &weaponInfo; }
	D2D_POINT_2F* getPoint() { return &dogPo; }
	int* getAddreesMoney() { return &money; }
	int* getAddreesMaxHp() { return &maxHP; }
	int* getAddreescurrentHp() { return &currentHP; }
	bool getisDead() { return _isDead; }
	bool getisTrans() { return _isTrans; }
	D2D_RECT_F* getClubRectMemory() { return &damageRect; }

	void plusMoney() { money++; };
	void plusHealth() {
		currentHP += 2;
		if (currentHP >= maxHP) {
			currentHP = maxHP;
		}
	};
	void plusBullet() {
		weaponInfo.aWeapon[weaponInfo.currentWeapon].bulletNum += 10;
		if (weaponInfo.aWeapon[weaponInfo.currentWeapon].bulletNum >= weaponInfo.aWeapon[weaponInfo.currentWeapon].bulletMax) {
			weaponInfo.aWeapon[weaponInfo.currentWeapon].bulletNum = weaponInfo.aWeapon[weaponInfo.currentWeapon].bulletMax;
		}
	}

	float checkUserCollision(D2D_RECT_F rect);
	EViEWDIRECTION getView() { return viewDirection; }
	bool getIsAir() { return _inAir; }

	void cheatKey();
	void addObjectRect(D2D1_RECT_F* rect);
	void deleteObjectRect(D2D1_RECT_F* rect);

	void useItem(int num) {
		switch (num) {
		case 0:
			//health
			maxHP += 5;
			currentHP = maxHP;
			CAMERAMANAGER->textOut(L"최대체력이 5증가 했습니다");
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			break;
		case 1:
			//upgrade
			if (weaponInfo.currentWeapon != 0) {
				weaponInfo.aWeapon[weaponInfo.currentWeapon].upgrade += 3;
				CAMERAMANAGER->textOut(L"현재 무기가 업그레이드 됬습니다");
				SOUNDMANAGER->play("event", 1.0f * effectSound);
				if (weaponInfo.aWeapon[weaponInfo.currentWeapon].upgrade >= UPGRADEMAX) {
					weaponInfo.aWeapon[weaponInfo.currentWeapon].upgrade = UPGRADEMAX;
					CAMERAMANAGER->textOut(L"현재 무기가 최대 업그레이드 됬습니다");
				}
			}
			else {
				addSpeed += 1;
				speed += addSpeed;
				SOUNDMANAGER->play("event", 1.0f * effectSound);
				CAMERAMANAGER->textOut(L"속도가 미약하지만 증가했습니다");
			}
			
			break;
		case 2:
			//bullet
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			CAMERAMANAGER->textOut(L"모든 총알을 수급했습니다");
			for (int i = 1; i < 6; ++i) {
				weaponInfo.aWeapon[i].bulletNum = weaponInfo.aWeapon[i].bulletMax;
			}
			break;
		}
	}


	sSaveData getSaveData();
	void loadData(sSaveData& data);
	void levelCorrect(int level) {
		switch (level)
		{
		case 0:
			maxHP = 30;
			currentHP = 30;

			weaponInfo.aWeapon[1].upgrade = 10;

			weaponInfo.aWeapon[2].upgrade = 10;

			weaponInfo.aWeapon[3].upgrade = 10;

			weaponInfo.aWeapon[4].upgrade = 10;

			weaponInfo.aWeapon[5].upgrade = 10;
			break;
		case 1:
			maxHP = 20;
			currentHP = 20;

			weaponInfo.aWeapon[1].upgrade = 5;

			weaponInfo.aWeapon[2].upgrade = 5;

			weaponInfo.aWeapon[3].upgrade = 5;

			weaponInfo.aWeapon[4].upgrade = 5;

			weaponInfo.aWeapon[5].upgrade = 5;
			break;
		case 2:
			maxHP = 10;
			currentHP = 10;

			weaponInfo.aWeapon[1].upgrade = 0;

			weaponInfo.aWeapon[2].upgrade = 0;

			weaponInfo.aWeapon[3].upgrade = 0;

			weaponInfo.aWeapon[4].upgrade = 0;

			weaponInfo.aWeapon[5].upgrade = 0;
			break;
		}
	}
};