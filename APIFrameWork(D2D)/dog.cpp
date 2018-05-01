#include "stdafx.h"
#include "dog.h"

dog::dog()
{
}


dog::~dog()
{
}

HRESULT dog::init(tstring mapName)
{
	CAMERAMANAGER->setStart();
	SOUNDMANAGER->play("start", 1.0f * effectSound);
	//setjumpPo = false;
	//jumpPo = {0,0};
	_isAttack = false;
	_isLeft = false;
	_inAir = false;
	_isJump = false;
	_isMove = false;
	_isHill = false;
	_isDead = false;
	_haveBoots = false;
	_bootsJump = false;
	jumpstate = EJUMPSTATE_NONE;
	_isTrans = false;
	transTime = 0;
	addSpeed = 0;
	initForWeapon();
	weaponInfo.currentWeapon = EWEAPON_NONE;

	speed = 3.6f;
	jumppower = 12.45f;
	gravity = 0;
	dogPo.x = 1000; //WINSIZEX_NUM / 2;
	dogPo.y = 900; //WINSIZEY_NUM / 2;
	
	boxs = new CollisionManager;
	boxs->init(&dogPo, 32, 63, mapName);
	
	CAMERAMANAGER->setPositionMemotyRick(&dogPo);
	CAMERAMANAGER->setDirectionMemotyRick(&viewDirection);

	money = 0;
	maxHP = 30;
	currentHP = 30;

	ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle");
	ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run");

	_mapName = mapName;
	return S_OK;
}

void dog::release(void)
{
	SAFE_DELETE(boxs);
}

void dog::update(tstring mapName)
{
	_mapName = mapName;
	cheatKey();
	jump();
	isAir();
	hill();
	fall();
	boxs->update(mapName);
	if (!_isDead) {
		whereView();
		swapWeapon();
		move();
		attack();
	}
	

	//부츠있는지 확인
	for (int i = 0; i < inventory.size(); ++i) {
		if (inventory.at(i) == EINVENITEN_BOOTS) {
			_haveBoots = true;
			break;
		}
		_haveBoots = false;
	}

	//트랜스상태변환
	if (_isTrans && TIMEMANAGER->getWorldTime() >= transTime) {
		_isTrans = false;
		transTime = 0;
	}
}

void dog::render(void)
{
	if (_isLeft) {
		reverseImage(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, IMAGEMANAGER->findImage(L"Dog_none_idle")->getHeight());
	}
	
	if (_isDead) {
		IMAGEMANAGER->findImage(L"Dog_dead")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_die"));
	}
	else if (_isAttack && weaponInfo.currentWeapon == EWEAPON_CLUP) {
		switch (viewDirection)
		{
		case EViEWDIRECTION_UP:
			IMAGEMANAGER->findImage(L"Dog_club_attack_up")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_club_attack_up"));
			if (_isTrans)IMAGEMANAGER->findImage(L"Dog_club_attack_up")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_club_attack_up"), RedBrush);
			break;
		case EViEWDIRECTION_DOWN:
			break;
		case EViEWDIRECTION_LEFT:
		case EViEWDIRECTION_RIGHT:
			IMAGEMANAGER->findImage(L"Dog_club_attack")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_club_attack"));
			if (_isTrans)IMAGEMANAGER->findImage(L"Dog_club_attack")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_club_attack"), RedBrush);
			break;
		}
	}
	else {
		if (jumpstate == EJUMPSTATE_NONE) {
			if (_isMove) {
				if (viewDirection == EViEWDIRECTION_UP && weaponInfo.currentWeapon != (int)EWEAPON_NONE) {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up"));
					if (_isTrans) IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up"), RedBrush);
				}
				else {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run"));
					if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run"), RedBrush);
				}
			}
			else {
				if (viewDirection == EViEWDIRECTION_UP && weaponInfo.currentWeapon != (int)EWEAPON_NONE) {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up"));
					if (_isTrans) IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up"), RedBrush);
				}
				else {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle"));
					if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle"), RedBrush);
				}
			}
		}
		else {
			switch (jumpstate)
			{
			case EJUMPSTATE_READY:
				IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready"));
				if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready"), RedBrush);
				break;
			case EJUMPSTATE_UPING:
				if (weaponInfo.currentWeapon != (int)EWEAPON_NONE) {
					switch (viewDirection)
					{
					case EViEWDIRECTION_UP:
						IMAGEMANAGER->bottomRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_up", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y);
						if (_isTrans)IMAGEMANAGER->bottomFillOpacityRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_up", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, RedBrush);
						break;
					case EViEWDIRECTION_DOWN:
						IMAGEMANAGER->bottomRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_down", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 30 }).y);
						if (_isTrans) IMAGEMANAGER->bottomFillOpacityRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_down", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 30 }).y, RedBrush);
						break;
					default:
						IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 4 }).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing"));
						if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 4 }).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing"), RedBrush);
						break;
					}
				}
				else {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing"));
					if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing"), RedBrush);
				}
				break;
			case EJUMPSTATE_DOWNING:
				if (weaponInfo.currentWeapon != (int)EWEAPON_NONE) {
					switch (viewDirection)
					{
					case EViEWDIRECTION_UP:
						IMAGEMANAGER->bottomRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_up", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y);
						if (_isTrans) IMAGEMANAGER->bottomFillOpacityRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_up", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, RedBrush);
						break;
					case EViEWDIRECTION_DOWN:
						IMAGEMANAGER->bottomRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_down", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 30 }).y);
						if (_isTrans) IMAGEMANAGER->bottomFillOpacityRender(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_down", Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition({ dogPo.x, dogPo.y + 30 }).y, RedBrush);
						break;
					default:
						IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing"));
						if (_isTrans)IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing"), RedBrush);
						break;
					}
				}
				else {
					IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing"));
					if (_isTrans) IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing"), RedBrush);
				}
				break;
			case EJUMPSTATE_END:
				IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end"));
				if (_isTrans) IMAGEMANAGER->findImage(L"Dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end")->aniBottomFillOpacityRender(Rt, CAMERAMANAGER->getAbsPosition(dogPo).x, CAMERAMANAGER->getAbsPosition(dogPo).y, ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end"), RedBrush);
				break;
			}
		}
	}
	Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	if(_isTrans) IMAGEMANAGER->render(L"redHeart", Rt);
	boxs->render();
	//D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ damageRect.left ,damageRect.top }).x,CAMERAMANAGER->getAbsPosition({ damageRect.left ,damageRect.top }).y, CAMERAMANAGER->getAbsPosition({ damageRect.right ,damageRect.bottom }).x,CAMERAMANAGER->getAbsPosition({ damageRect.right ,damageRect.bottom }).y }, WhiteBrush);
}

void dog::initForWeapon()
{
	weaponInfo.aWeapon[0].kind = EWEAPON_NONE;
	weaponInfo.aWeapon[0].name = L"none";
	weaponInfo.aWeapon[0].upgrade = NULL;
	weaponInfo.aWeapon[0].bulletMax = NULL;
	weaponInfo.aWeapon[0].bulletNum = NULL;

	weaponInfo.aWeapon[1].kind = EWEAPON_CLUP;
	weaponInfo.aWeapon[1].name = L"club";
	weaponInfo.aWeapon[1].upgrade = 0;
	weaponInfo.aWeapon[1].bulletMax = NULL;
	weaponInfo.aWeapon[1].bulletNum = NULL;

	weaponInfo.aWeapon[2].kind = EWEAPON_GUN;
	weaponInfo.aWeapon[2].name = L"gun";
	weaponInfo.aWeapon[2].upgrade = 0;
	weaponInfo.aWeapon[2].bulletMax = 50;
	weaponInfo.aWeapon[2].bulletNum = 50;

	weaponInfo.aWeapon[3].kind = EWEAPON_SHOTGUN;
	weaponInfo.aWeapon[3].name = L"shotgun";
	weaponInfo.aWeapon[3].upgrade = 0;
	weaponInfo.aWeapon[3].bulletMax = 25;
	weaponInfo.aWeapon[3].bulletNum = 25;

	weaponInfo.aWeapon[4].kind = EWEAPON_ROCKET;
	weaponInfo.aWeapon[4].name = L"rocket";
	weaponInfo.aWeapon[4].upgrade = 0;
	weaponInfo.aWeapon[4].bulletMax = 10;
	weaponInfo.aWeapon[4].bulletNum = 10;

	weaponInfo.aWeapon[5].kind = EWEAPON_PLASMA;
	weaponInfo.aWeapon[5].name = L"plasma";
	weaponInfo.aWeapon[5].upgrade = 0;
	weaponInfo.aWeapon[5].bulletMax = 20;
	weaponInfo.aWeapon[5].bulletNum = 20;
}

void dog::move()
{
	if (KEYMANAGER->isStayKeyDown(_mGameKey.RIGHT) && KEYMANAGER->isStayKeyDown(_mGameKey.LEFT)) {
		_isMove = false;
		if (SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->stop("walk");
		}
	}

	if (KEYMANAGER->isStayKeyDown(_mGameKey.LEFT) && !KEYMANAGER->isStayKeyDown(_mGameKey.RIGHT)) {
		boxs->updateRectPosi();
		if (!SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->play("walk", 1.0f * effectSound);
		}
		if (!_isLeft) {
			_isLeft = true;
		}
		_isMove = true;
		if (!boxs->checkCollisionLeft()) {
			float tmp = boxs->checkCollisionBottom();
			if (tmp == 0.0f) {
				dogPo.x -= speed;
				while (boxs->checkCollisionLeft()) {
					dogPo.x += 0.1f;
					boxs->updateRectPosi();
				}
			}
			else {
				tmp = 1;
				if (cosf(tmp*(PI / 180)) * speed <= 0) {
					dogPo.x += cosf(tmp*(PI / 180)) * speed;
					dogPo.y -= sinf(tmp*(PI / 180)) * speed;
					while (boxs->checkCollisionLeft()) {
						dogPo.x += 0.1f;
						boxs->updateRectPosi();
					}
				}
				else {
					dogPo.x -= cosf(tmp*(PI / 180)) * speed;
					dogPo.y += sinf(tmp*(PI / 180)) * speed;
					while (boxs->checkCollisionLeft()) {
						dogPo.x += 0.1f;
						boxs->updateRectPosi();
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(_mGameKey.RIGHT) && !KEYMANAGER->isStayKeyDown(_mGameKey.LEFT)) {
		boxs->updateRectPosi();
		if (!SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->play("walk", 1.0f * effectSound);
		}
		if (_isLeft) {
			_isLeft = false;
		}
		_isMove = true;
		if (!boxs->checkCollisionRight()) {
			float tmp = boxs->checkCollisionBottom();
			if (tmp == 0.0f) {
				dogPo.x += speed;
				while (boxs->checkCollisionRight()) {
					dogPo.x -= 0.1f;
					boxs->updateRectPosi();
				}
			}
			else {
				tmp = 1;
				if (cosf(tmp*(PI / 180)) * speed >= 0) {
					dogPo.x += cosf(tmp*(PI / 180)) * speed;
					dogPo.y -= sinf(tmp*(PI / 180)) * speed;
					while (boxs->checkCollisionRight()) {
						dogPo.x -= 0.1f;
						boxs->updateRectPosi();
					}
				}
				else {
					dogPo.x -= cosf(tmp*(PI / 180)) * speed;
					dogPo.y += sinf(tmp*(PI / 180)) * speed;
					while (boxs->checkCollisionRight()) {
						dogPo.x -= 0.1f;
						boxs->updateRectPosi();
					}
				}
			}
		}
	}
	
	if (KEYMANAGER->isOnceKeyUp(_mGameKey.LEFT)) {
		_isMove = false;
		if (SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->stop("walk");
		}
		while (boxs->checkCollisionLeft()) {
			dogPo.x += 0.1f;
			boxs->updateRectPosi();
		}
	}
	if (KEYMANAGER->isOnceKeyUp(_mGameKey.RIGHT)) {
		_isMove = false;
		if (SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->stop("walk");
		}
		while (boxs->checkCollisionRight()) {
			dogPo.x -= 0.1f;
			boxs->updateRectPosi();
		}
	}
}

void dog::isAir()
{
	if (boxs->checkCollisionBottom()) {
		switch (jumpstate)
		{
		case EJUMPSTATE_NONE:
			_isJump = false;
			_inAir = false;
			_bootsJump = false;
			gravity = 0;
			while (boxs->checkCollisionBottom() != 0.0f) {
				dogPo.y -= 0.2f;
				boxs->updateRectPosi();
			}
			dogPo.y += 0.2f;
			break;
		case EJUMPSTATE_READY:
			_isJump = false;
			_inAir = false;
			_bootsJump = false;
			gravity = 0;
			while (boxs->checkCollisionBottom() != 0.0f) {
				dogPo.y -= 0.2f;
				boxs->updateRectPosi();
			}
			dogPo.y += 0.2f;
			break;
		case EJUMPSTATE_DOWNING:
			//setjumpPo = false;
			jumpstate = EJUMPSTATE_END;
			if (!SOUNDMANAGER->isPlaySound("land")) {
				SOUNDMANAGER->play("land", 1.0f * effectSound);
			}
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end");
			_isJump = false;
			_inAir = false;
			_bootsJump = false;
			gravity = 0;
			while (boxs->checkCollisionBottom() != 0.0f) {
				dogPo.y -= 0.2f;
				boxs->updateRectPosi();
			}
			dogPo.y += 0.2f;
			break;
		}
	}
	else if (_isHill) {
		if (boxs->checkCollisionHill()) {
			switch (jumpstate)
			{
			case EJUMPSTATE_NONE:
				_isJump = false;
				_inAir = false;
				_bootsJump = false;
				gravity = 0;
				while (boxs->checkCollisionHill()) {
					dogPo.y -= 0.2f;
					boxs->updateRectPosi();
				}
				dogPo.y += 0.2f;
				break;
			case EJUMPSTATE_READY:
				_isJump = false;
				_bootsJump = false;
				_inAir = false;
				gravity = 0;
				while (boxs->checkCollisionHill()) {
					dogPo.y -= 0.2f;
					boxs->updateRectPosi();
				}
				dogPo.y += 0.2f;
				break;
			case EJUMPSTATE_DOWNING:
				jumpstate = EJUMPSTATE_END;
				if (!SOUNDMANAGER->isPlaySound("land")) {
					SOUNDMANAGER->play("land", 1.0f * effectSound);
				}
				ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end");
				_isJump = false;
				_bootsJump = false;
				_inAir = false;
				gravity = 0;
				while (boxs->checkCollisionHill()) {
					dogPo.y -= 0.2f;
					boxs->updateRectPosi();
				}
				dogPo.y += 0.2f;
				break;
			}
		}
		else {
			_isHill = false;
		}
		
	}
	else {
		_inAir = true;
	}
}

void dog::jump()
{
	if (KEYMANAGER->isOnceKeyDown(_mGameKey.JUMP) && !_isDead) {
		if (!_isJump && jumpstate == EJUMPSTATE_NONE) {
			jumpstate = EJUMPSTATE_READY;
			//if (!setjumpPo) {
			//	jumpPo = dogPo;
			//	setjumpPo = true;
			//}
			if (!SOUNDMANAGER->isPlaySound("jump")) {
				SOUNDMANAGER->play("jump", 1.0f * effectSound);
			}
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready");
		}
		if (_haveBoots && !_bootsJump && (jumpstate == EJUMPSTATE_DOWNING || jumpstate == EJUMPSTATE_UPING)) {
			_bootsJump = true;
			gravity = 0;
			//Bif (!setjumpPo) {
			//B	jumpPo = dogPo;
			//B	setjumpPo = true;
			//B}
			if (!SOUNDMANAGER->isPlaySound("jump")) {
				SOUNDMANAGER->play("jump", 1.0f * effectSound);
			}
			jumpstate = EJUMPSTATE_READY;
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready");
		}
	}

	if(jumpstate != EJUMPSTATE_NONE){
		if (SOUNDMANAGER->isPlaySound("walk")) {
			SOUNDMANAGER->stop("walk");
		}
	}

	switch (jumpstate)
	{
	case EJUMPSTATE_READY:
		if (!ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ready")->isPlay()) {
			_isJump = true;
			_isHill = false;
			jumpstate = EJUMPSTATE_UPING;
			ANIMATIONMANAGER->start(L"jumpEffect");
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_jump_ing");
		}
		break;
	case EJUMPSTATE_END:
		if (!ANIMATIONMANAGER->findAnimation(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_end")->isPlay()) {
			jumpstate = EJUMPSTATE_NONE;
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle");
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run");
			if (weaponInfo.currentWeapon != 0) {
				ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up");
				ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up");
			}
		}
		break;
	}

	if (_isJump) {
		gravity += 0.5f;
		dogPo.y -= (jumppower - gravity);
		if (boxs->checkCollisionTop() || (jumppower <= gravity)) {
			while (boxs->checkCollisionTop() == true) {
				dogPo.y += 0.2f;
				boxs->updateRectPosi();
			}
			_isJump = false;
			_inAir = true;
			gravity = 0;
			jumpstate = EJUMPSTATE_DOWNING;
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing");
		}
	}
}

void dog::fall()
{
	if (_inAir && !_isJump && !_isHill) {
		if (gravity <= 30.f) {
			gravity += 0.5f;
		}
		dogPo.y += gravity;
		if (jumpstate != EJUMPSTATE_DOWNING && gravity >= 6.0f) {
			jumpstate = EJUMPSTATE_DOWNING;
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_fall_ing");
		}
	}
}

void dog::hill()
{
	if (jumpstate == EJUMPSTATE_DOWNING) {
		if (boxs->checkCollisionHill()) {
			_isHill = true;
		}
	}
}

void dog::attack()
{
	switch (weaponInfo.currentWeapon)
	{
	case EWEAPON_CLUP:
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.ATTACK) && !_isAttack) {
			SOUNDMANAGER->play("club", 1.0f * effectSound);
			_isAttack = true;
			switch (viewDirection)
			{
			case EViEWDIRECTION_LEFT:
				ANIMATIONMANAGER->start(L"dog_club_attack");
				damageRect.left = dogPo.x - 60;
				damageRect.right = dogPo.x - 20;
				damageRect.top = dogPo.y - 45;
				damageRect.bottom = dogPo.y - 20;
				break;
			case EViEWDIRECTION_RIGHT:
				ANIMATIONMANAGER->start(L"dog_club_attack");
				damageRect.left = dogPo.x + 20;
				damageRect.right = dogPo.x + 60;
				damageRect.top = dogPo.y - 45;
				damageRect.bottom = dogPo.y - 20;
				break;
			case EViEWDIRECTION_UP:
				ANIMATIONMANAGER->start(L"dog_club_attack_up");
				damageRect.left = dogPo.x - 15;
				damageRect.right = dogPo.x + 15;
				damageRect.top = dogPo.y - 90;
				damageRect.bottom = dogPo.y - 70;
				break;
			case EViEWDIRECTION_DOWN:
				break;
			}
			break;
		}
	}

	if (_isAttack && weaponInfo.currentWeapon == EWEAPON_CLUP) {
		if (!ANIMATIONMANAGER->findAnimation(L"dog_club_attack")->isPlay() && !ANIMATIONMANAGER->findAnimation(L"dog_club_attack_up")->isPlay()) {
			_isAttack = false;
		}
		switch (viewDirection)
		{
		case EViEWDIRECTION_LEFT:
			break;
		case EViEWDIRECTION_RIGHT:
			break;
		case EViEWDIRECTION_UP:
			break;
		case EViEWDIRECTION_DOWN:
			break;
		}
	}
	else {
		damageRect.left		= 0;
		damageRect.right	= 0;
		damageRect.top		= 0;
		damageRect.bottom	= 0;
	}

	if (_inAir && viewDirection == EViEWDIRECTION_DOWN && weaponInfo.currentWeapon == EWEAPON_CLUP) {
		damageRect.left = dogPo.x - 15;
		damageRect.right = dogPo.x + 15;
		damageRect.top = dogPo.y - 10;
		damageRect.bottom = dogPo.y + 10;
	}
}

void dog::swapWeapon()
{
	if (KEYMANAGER->isOnceKeyDown(_mGameKey.NEXT)) {
		if (weaponInfo.currentWeapon == 5) weaponInfo.currentWeapon = 0;
		else weaponInfo.currentWeapon += 1;
		ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle");
		ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run");
		if (weaponInfo.currentWeapon != 0) {
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up");
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up");
		}
		switch (weaponInfo.currentWeapon)
		{
		case EWEAPON_NONE:
			speed = 3.6f;
			speed += addSpeed;
			jumppower = 12.45f;
			break;
		case EWEAPON_CLUP:
			speed = 3.3f;
			speed += addSpeed;
			jumppower = 12.0f;
			break;
		case EWEAPON_GUN:
			speed = 3.3f;
			speed += addSpeed;
			jumppower = 12.0f;
			break;
		case EWEAPON_SHOTGUN:
		case EWEAPON_ROCKET:
		case EWEAPON_PLASMA:
			speed = 2.4f;
			speed += addSpeed;
			jumppower = 11.0f;
			break;
		}

	}
	if (KEYMANAGER->isOnceKeyDown(_mGameKey.BEFORE)) {
		if (weaponInfo.currentWeapon == 0) weaponInfo.currentWeapon = 5;
		else weaponInfo.currentWeapon -= 1;
		ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle");
		ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run");
		if (weaponInfo.currentWeapon != 0) {
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_idle_up");
			ANIMATIONMANAGER->start(L"dog_" + weaponInfo.aWeapon[weaponInfo.currentWeapon].name + L"_run_up");
		}
		switch (weaponInfo.currentWeapon)
		{
		case EWEAPON_NONE:
			speed = 3.6f;
			speed += addSpeed;
			jumppower = 12.45f;
			break;
		case EWEAPON_CLUP:
			speed = 3.3f;
			speed += addSpeed;
			jumppower = 12.0f;
			break;
		case EWEAPON_GUN:
			speed = 3.3f;
			speed += addSpeed;
			jumppower = 12.0f;
			break;
		case EWEAPON_SHOTGUN:
		case EWEAPON_ROCKET:
		case EWEAPON_PLASMA:
			speed = 2.4f;
			speed += addSpeed;
			jumppower = 11.0f;
			break;
		}
	}
}

void dog::whereView()
{
	if (_isLeft) {
		viewDirection = EViEWDIRECTION_LEFT;
	}
	else {
		viewDirection = EViEWDIRECTION_RIGHT;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		if (viewDirection != EViEWDIRECTION_UP) {
			viewDirection = EViEWDIRECTION_UP;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		if (viewDirection != EViEWDIRECTION_DOWN) {
			viewDirection = EViEWDIRECTION_DOWN;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP)) {
		if (_isLeft) {
			viewDirection = EViEWDIRECTION_LEFT;
		}
		else {
			viewDirection = EViEWDIRECTION_RIGHT;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN)) {
		if (_isLeft) {
			viewDirection = EViEWDIRECTION_LEFT;
		}
		else {
			viewDirection = EViEWDIRECTION_RIGHT;
		}
	}
}

float dog::checkUserCollision(D2D_RECT_F rect)
{
	return boxs->checkUserCollision(rect);
}

void dog::cheatKey()
{
	if (KEYMANAGER->isOnceKeyDown('I')) {
		setTrans(1000);
	}
	if (KEYMANAGER->isOnceKeyDown('O')) {
		if (weaponInfo.aWeapon[weaponInfo.currentWeapon].upgrade < UPGRADEMAX) {
			weaponInfo.aWeapon[weaponInfo.currentWeapon].upgrade++;
		}
	}
}

void dog::addObjectRect(D2D1_RECT_F * rect)
{ 
	boxs->addObjectRect(rect);
}

void dog::deleteObjectRect(D2D1_RECT_F * rect)
{
	boxs->deleteObjectRect(rect);
}

sSaveData dog::getSaveData()
{
	sSaveData tmp;
	tmp.addSpeed = addSpeed;
	tmp.currentHP = currentHP;
	for (int i = 0; i < inventory.size(); ++i) {
		tmp.inventory[i] = inventory.at(i);
	}
	tchar* name = (wchar_t *)_mapName.c_str();
	wsprintf(tmp.mapName, name);
	tmp.maxHP = maxHP;
	tmp.money = money;
	tmp.Position = dogPo;
	for (int i = 0; i < 6; ++i) {
		tmp.bulletMax[i] = weaponInfo.aWeapon[i].bulletMax;
		tmp.bulletNum[i] = weaponInfo.aWeapon[i].bulletNum;
		tmp.upgrade[i] = weaponInfo.aWeapon[i].upgrade;
	}
	tmp.currentWeapon = weaponInfo.currentWeapon;
	wsprintf(tmp.time, TIMEMANAGER->getCurrentInfo());
	return tmp;
}

void dog::loadData(sSaveData& data)
{
	inventory.clear();
	_isDead = false;
	for (int i = 0; i < 9; ++i) {
		if (data.inventory[i] == EINVENITEN_NONE || data.inventory[i] >= 7) {
			break;
		}
		inventory.push_back(data.inventory[i]);
	}
	for (int i = 0; i < 6; ++i) {
		weaponInfo.aWeapon[i].bulletMax = data.bulletMax[i];
		weaponInfo.aWeapon[i].bulletNum = data.bulletNum[i];
		weaponInfo.aWeapon[i].upgrade = data.upgrade[i];
	}
	weaponInfo.currentWeapon = 0;
	maxHP = data.maxHP;
	currentHP = data.currentHP;
	money = data.money;
	dogPo = data.Position;
	addSpeed = data.addSpeed;
	speed += data.addSpeed;

	jumpstate = EJUMPSTATE_NONE;
	CAMERAMANAGER->setCameraCenter();
}