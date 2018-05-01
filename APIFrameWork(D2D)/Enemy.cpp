#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(SENEMY _info, tstring _mapName)
{
	info = _info;
	imageName = info.name;
	image* tmpBG = IMAGEMANAGER->findImage(_mapName);
	position = { info.x * tmpBG->getWidth(), info.y * tmpBG->getHeight() };
	action = EENEMYACTKIND_STOP;
	gravity = 0;
	_isFollow = false;
	_isLeft = true;
	_isAir = false;
	_isDamage = false;
	_isDelete = false;
	create = false;
	damageNum = 0;
	orderBuffer = 0;
	if (imageName == L"slime_green") {
		// 30,26 (W,H)
		rect = { position.x - 30, position.y - 38, position.x + 30, position.y };
		position = { info.x * tmpBG->getWidth(), info.y * tmpBG->getHeight() + 26 };
		currentHP = 3;
		speed = 1.5f;
		boxs = new CollisionManager;
		boxs->init(&position, 60, 52, _mapName);

		aniIDLE = new animation;
		aniIDLE->init(172 * 2, 26 * 2, 172 * 2 /4, 26 * 2);
		aniIDLE->setDefPlayFrame(false, true);
		aniIDLE->setFPS(8);
		aniIDLE->start();

		aniDEAD = new animation;
		aniDEAD->init(215 * 2, 25 * 2, 215 * 2/5, 25 * 2);
		aniDEAD->setDefPlayFrame(false, false);
		aniDEAD->setFPS(8);

		ANIMATIONMANAGER->start(imageName + L"_damage");
	}
	else if (imageName == L"spider") {
		//36, 30
		rect = { position.x - 36, position.y - 60, position.x + 36, position.y };
		position = { info.x * tmpBG->getWidth(), info.y * tmpBG->getHeight() + 30 };
		currentHP = 6;
		speed = 2.5f;
		boxs = new CollisionManager;
		boxs->init(&position, 60, 52, _mapName);
		aniIDLE = new animation;
		aniIDLE->init(420 * 2, 31 * 2, 420 * 2 /5, 31 * 2);
		aniIDLE->setDefPlayFrame(false, true);
		aniIDLE->setFPS(8);
		aniIDLE->start();
		aniMOVE = new animation;
		aniMOVE->init(342 * 2, 30 * 2, 342 * 2/6, 30 * 2);
		aniMOVE->setDefPlayFrame(false, true);
		aniMOVE->setFPS(8);
		aniMOVE->start();
		aniDEAD = new animation;
		aniDEAD->init(390 * 2, 38 * 2, 390 * 2/6, 38 * 2);
		aniDEAD->setDefPlayFrame(false, false);
		aniDEAD->setFPS(8);
		ANIMATIONMANAGER->start(imageName + L"_damage");
	}
	else if (imageName == L"rat") {
		//36, 30
		rect = { position.x - 28, position.y - 60, position.x + 50, position.y };
		currentHP = 10;
		speed = 4.5f;
		boxs = new CollisionManager;
		boxs->init(&position, 60, 52, _mapName);
		aniIDLE = new animation;
		aniIDLE->init(260 * 2, 32 * 2, 260 * 2/4, 32 * 2);
		aniIDLE->setDefPlayFrame(false, true);
		aniIDLE->setFPS(8);
		aniIDLE->start();
		aniMOVE = new animation;
		aniMOVE->init(390 * 2, 34 * 2, 390 * 2/6, 34 * 2);
		aniMOVE->setDefPlayFrame(false, true);
		aniMOVE->setFPS(8);
		aniMOVE->start();
		aniDEAD = new animation;
		aniDEAD->init(390 * 2, 34 * 2, 390 * 2/6, 34 * 2);
		aniDEAD->setDefPlayFrame(false, false);
		aniDEAD->setFPS(8);
		ANIMATIONMANAGER->start(imageName + L"_damage");
	}
	else if (imageName == L"egg") {
		//30, 26
		aniIDLE = new animation;
		aniIDLE->init(96 * 2, 26 * 2, 96 * 2/2, 26 * 2);
		aniIDLE->setDefPlayFrame(false, true);
		aniIDLE->setFPS(8);
		aniIDLE->start();
		ANIMATIONMANAGER->start(imageName + L"_damage");
		rect = { position.x - 30, position.y - 26, position.x + 30, position.y + 26 };
		currentHP = 2;
	}
	return S_OK;
}

void Enemy::release(void)
{
	SAFE_DELETE(boxs);
}

void Enemy::update(tstring mapName)
{
	if (imageName == L"slime_green") {
		rect = { position.x - 30, position.y - 38, position.x + 30, position.y };
		boxs->update(mapName);
		actionOrder();
		move();
		Fall();
		aniIDLE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		aniDEAD->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
	}
	else if (imageName == L"spider") {
		rect = { position.x - 36, position.y - 60, position.x + 36, position.y };
		boxs->update(mapName);
		actionOrder();
		move();
		Fall();
		aniIDLE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		aniMOVE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		aniDEAD->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
	}
	else if (imageName == L"rat") {
		rect = { position.x - 28, position.y - 60, position.x + 50, position.y };
		boxs->update(mapName);
		actionOrder();
		move();
		Fall();
		aniIDLE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		aniMOVE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		aniDEAD->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
	}
	else if (imageName == L"egg") {
		aniIDLE->frameUpdate(TIMEMANAGER->getElapsedTime()*1.0f);
		if (_isDamage && action != EENEMYACTKIND_DEATH) {
			currentHP--;
			_isDamage = false;
			action = EENEMYACTKIND_ATTACK;
			orderBuffer = TIMEMANAGER->getWorldTime() + 1;
		}
		if (currentHP <= 0 && action != EENEMYACTKIND_DEATH) {
			action = EENEMYACTKIND_DEATH;
		}
		if (action == EENEMYACTKIND_ATTACK && orderBuffer <= TIMEMANAGER->getWorldTime()) {
			action = EENEMYACTKIND_STOP;
		}
		if (action != EENEMYACTKIND_DEATH &&
			(position.x <= dogPosition->x + 200 && position.x >= dogPosition->x - 200 && position.y <= dogPosition->y + 100 && position.y >= dogPosition->y - 100)) {
			create = true;
		}
		if (action == EENEMYACTKIND_DEATH){
			_isDelete = true;
		}
	}
}

void Enemy::render(void)
{
	if (!_isLeft) {
		reverseImage(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, IMAGEMANAGER->findImage(imageName + L"_idle")->getHeight());
	}
	switch (action)
	{
	case EENEMYACTKIND_STOP:
		if (imageName == L"egg") {
			IMAGEMANAGER->findImage(imageName + L"_idle")->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, aniIDLE);
		}
		else {
			IMAGEMANAGER->findImage(imageName + L"_idle")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, aniIDLE);
		}
		break;
	case EENEMYACTKIND_MOVE:
		if (imageName == L"slime_green") {
			IMAGEMANAGER->findImage(imageName + L"_idle")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, aniIDLE);
		}
		else {
			IMAGEMANAGER->findImage(imageName + L"_move")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, aniMOVE);
		}
		break;
	case EENEMYACTKIND_ATTACK:
		if (imageName == L"egg") {
			IMAGEMANAGER->findImage(imageName + L"_damage")->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName + L"_damage"));

		}
		else {
			IMAGEMANAGER->findImage(imageName + L"_damage")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName + L"_damage"));
		}
		break;
	case EENEMYACTKIND_DEATH:
		if (imageName == L"egg") {
			IMAGEMANAGER->render(L"egg_death", Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
		}
		else {
			IMAGEMANAGER->findImage(imageName + L"_death")->aniBottomRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, aniDEAD);
		}
		break;
	}
	Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	//D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({rect.left, rect.top}).x, CAMERAMANAGER->getAbsPosition({ rect.left, rect.top }).y,CAMERAMANAGER->getAbsPosition({ rect.right, rect.bottom }).x, CAMERAMANAGER->getAbsPosition({ rect.right, rect.bottom }).y }, Brush);
}

void Enemy::actionOrder()
{
	if (_isDamage && action != EENEMYACTKIND_DEATH) {
		currentHP -= damageNum;
		_isDamage = false;
		EFFECTMANAGER->play(L"bullet_hit", position.x, position.y - 20);
		EFFECTMANAGER->play(L"Dam", position.x, position.y - 20);
		action = EENEMYACTKIND_ATTACK;
		orderBuffer = TIMEMANAGER->getWorldTime() + 1;
	}
	if (currentHP <= 0 && action != EENEMYACTKIND_DEATH) {
		action = EENEMYACTKIND_DEATH;
		if (imageName == L"slime_green") SOUNDMANAGER->play("slimeDeath", 1.0f * effectSound);
		else if (imageName == L"egg") SOUNDMANAGER->play("ArachnideSpawn", 1.0f * effectSound);
		else if (imageName == L"spider") SOUNDMANAGER->play("ArachnideDie", 1.0f * effectSound);
		aniDEAD->start();
	}
	switch (action)
	{
	case EENEMYACTKIND_STOP:
	case EENEMYACTKIND_MOVE: {
		if (imageName != L"rat") {
			if (position.x >= dogPosition->x + 1000 || position.x <= dogPosition->x - 1000 || position.y >= dogPosition->y + 300 || position.y <= dogPosition->y - 300) {
				action = EENEMYACTKIND_STOP;
				orderBuffer = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(1, 3);
			}
			else {
				if (position.x <= dogPosition->x + 800 && position.x >= dogPosition->x - 800 && position.y <= dogPosition->y + 100 && position.y >= dogPosition->y - 100) {
					_isFollow = true;
					action = EENEMYACTKIND_MOVE;
					if (position.x <= dogPosition->x) _isLeft = false;
					else _isLeft = true;
				}
				else {
					if (orderBuffer <= TIMEMANAGER->getWorldTime()) {
						_isFollow = false;
						_isLeft = (bool)RND->getInt(2);
						switch (RND->getInt(3))
						{
						case 0:
							action = EENEMYACTKIND_STOP;
							break;
						case 1:
							action = EENEMYACTKIND_MOVE;
							break;
						case 2:
							action = EENEMYACTKIND_MOVE;
							break;
						}
						orderBuffer = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(1, 3);
					}
				}
			}
		}
		else {
			if (position.x >= dogPosition->x + 2000 || position.x <= dogPosition->x - 2000 || position.y >= dogPosition->y + 1000 || position.y <= dogPosition->y - 1000) {
				action = EENEMYACTKIND_STOP;
				orderBuffer = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(1, 3);
			}
			else {
				if (position.x <= dogPosition->x + 1500 && position.x >= dogPosition->x - 1500 && position.y <= dogPosition->y + 900 && position.y >= dogPosition->y - 900) {
					_isFollow = true;
					action = EENEMYACTKIND_MOVE;
					if (position.x <= dogPosition->x) _isLeft = false;
					else _isLeft = true;
				}
				else {
					if (orderBuffer <= TIMEMANAGER->getWorldTime()) {
						_isFollow = false;
						_isLeft = (bool)RND->getInt(2);
						switch (RND->getInt(3))
						{
						case 0:
							action = EENEMYACTKIND_STOP;
							break;
						case 1:
							action = EENEMYACTKIND_MOVE;
							break;
						case 2:
							action = EENEMYACTKIND_MOVE;
							break;
						}
						orderBuffer = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(1, 3);
					}
				}
			}
		}
		}break;
	case EENEMYACTKIND_ATTACK:
		if (TIMEMANAGER->getWorldTime() >= orderBuffer) {
			action = EENEMYACTKIND_STOP;
		}
		break;
	case EENEMYACTKIND_DEATH:
		if (!aniDEAD->isPlay()) {
			_isDelete = true;
		}
		break;
	}
}

void Enemy::move()
{
	switch (action)
	{
	case EENEMYACTKIND_MOVE:
		if (_isLeft) {
			if (!boxs->checkCollisionLeft()) {
				float tmp = boxs->checkCollisionBottom();
				if (tmp == 0.0f) {
					position.x -= speed;
					while (boxs->checkCollisionLeft()) {
						position.x += 0.1f;
						boxs->updateRectPosi();
					}
				}
				else {
					if (cosf(tmp*(PI / 180)) * speed <= 0) {
						position.x += cosf(tmp*(PI / 180)) * speed;
						position.y -= sinf(tmp*(PI / 180)) * speed;
						while (boxs->checkCollisionLeft()) {
							position.x += 0.1f;
							boxs->updateRectPosi();
						}
					}
					else {
						position.x -= cosf(tmp*(PI / 180)) * speed;
						position.y += sinf(tmp*(PI / 180)) * speed;
						while (boxs->checkCollisionLeft()) {
							position.x += 0.1f;
							boxs->updateRectPosi();
						}
					}
				}
			}
		}
		else {
			if (!boxs->checkCollisionRight()) {
				float tmp = boxs->checkCollisionBottom();
				if (tmp == 0.0f) {
					position.x += speed;
					while (boxs->checkCollisionRight()) {
						position.x -= 0.1f;
						boxs->updateRectPosi();
					}
				}
				else {
					if (cosf(tmp*(PI / 180)) * speed >= 0) {
						position.x += cosf(tmp*(PI / 180)) * speed;
						position.y -= sinf(tmp*(PI / 180)) * speed;
						while (boxs->checkCollisionRight()) {
							position.x -= 0.1f;
							boxs->updateRectPosi();
						}
					}
					else {
						position.x -= cosf(tmp*(PI / 180)) * speed;
						position.y += sinf(tmp*(PI / 180)) * speed;
						while (boxs->checkCollisionRight()) {
							position.x -= 0.1f;
							boxs->updateRectPosi();
						}
					}
				}
			}
		}
		break;
	}

}

void Enemy::Fall()
{
	if (boxs->checkCollisionBottom()) {
		gravity = 0;
		_isAir = false;
		while (boxs->checkCollisionBottom() != 0.0f) {
			position.y -= 0.2f;
			boxs->updateRectPosi();
		}
		position.y += 0.2f;
	}
	else {
		_isAir = true;
	}

	if (_isAir) {
		gravity += 0.2f;
		position.y += gravity;
	}
}

HRESULT Enemy_BOSS::init(SENEMY _info, tstring _mapName)
{
	Enemy::init(_info, _mapName);
	action = EBOSSACTION_IDLE;
	frameX = 0;
	count = 0;
	rect = { position.x - 90, position.y - 110, position.x + 90, position.y + 110 };
	currentHP = 200;
	speed = 2.5f;


	ANIMATIONMANAGER->start(L"1st_boss_idle");
	if (!SOUNDMANAGER->isPlaySound("bossBGM")) {
		SOUNDMANAGER->play("bossBGM", 1.0f * bgmSound);
	}
	hpBar = new progressBar;
	hpBar->init(L"images/UI/ingame/bossbar_front.png", 260 + 18, WINSIZEY_NUM - 130 + 17, 359 * 2, 7 * 2);

	maxHP = 200;
	hpBar->setGauge((float)currentHP, (float)maxHP);
	bulletBlankTime = TIMEMANAGER->getWorldTime() + 0.5f;
	return S_OK;
}

void Enemy_BOSS::release(void)
{
	SAFE_DELETE(hpBar);
	Enemy::release();
}

void Enemy_BOSS::update(tstring mapName)
{
	rect = { position.x - 90, position.y - 110, position.x + 90, position.y + 110 };
	hpBar->setGauge((float)currentHP, (float)maxHP);
	if (!_isDelete) {
		if (action != EBOSSACTION_DEAD) {
			fireBullet();
			moveBullet();
			move();
			if (_isDamage) {
				_isDamage = false;
				if (TIMEMANAGER->getWorldTime() >= orderBuffer) {
					create = true;
					orderBuffer = TIMEMANAGER->getWorldTime() + 0.3f;
				}
				currentHP -= damageNum;

				if (currentHP <= 0) {
					currentHP = 0;
					SOUNDMANAGER->stop("bossBGM");
					SOUNDMANAGER->stop("bossMove");
					SOUNDMANAGER->play("bossDeath", 1.0f * effectSound);
					action = EBOSSACTION_DEAD;
				}

				if (position.y >= 610) {
					position.y = 610;
				}
				else position.y += damageNum;
			}
		}
		else {
			if (!ANIMATIONMANAGER->findAnimation(L"1st_boss_die")->isPlay()) {
				ANIMATIONMANAGER->start(L"1st_boss_die");
				deadPoint = position.y;
				_isDelete = true;
				vBullet.clear();
			}
		}
	}
	else {
		if (position.y >= 850) position.y = 850;
		else position.y += 5.0f;
		if (deadPoint >= 610) deadPoint = 610;
		else deadPoint += 5.0f;
	}
}

void Enemy_BOSS::render(void)
{
	if (_isDelete) {
		IMAGEMANAGER->render(L"1st_boss_bar", Rt, CAMERAMANAGER->getAbsPosition({ 130, 0 }).x, CAMERAMANAGER->getAbsPosition({0,deadPoint }).y);
	}
	else {
		IMAGEMANAGER->render(L"1st_boss_bar", Rt, CAMERAMANAGER->getAbsPosition({ 130, 0 }).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
	//보스출력
	switch (action)
	{
	case EBOSSACTION_IDLE:
		IMAGEMANAGER->findImage(L"1st_boss_idle")->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(L"1st_boss_idle"));
		break;
	case EBOSSACTION_FIRE:
		IMAGEMANAGER->frameRender(L"1st_boss_attack", Rt, frameX, 0, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
		break;
	case EBOSSACTION_DEAD:
		IMAGEMANAGER->findImage(L"1st_boss_die")->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(L"1st_boss_die"));
		break;
	}

	for (int i = 0; i < vBullet.size(); ++i) {
		IMAGEMANAGER->render(L"1st_boss_bullet", Rt, CAMERAMANAGER->getAbsPosition(vBullet.at(i).point).x, CAMERAMANAGER->getAbsPosition(vBullet.at(i).point).y);
	}

	IMAGEMANAGER->render(L"bossbar_back", Rt);
	hpBar->render();
}

void Enemy_BOSS::fireBullet()
{
	if (TIMEMANAGER->getWorldTime()>= bulletBlankTime) {  // fire상태
		action = EBOSSACTION_FIRE;
		count++;
		if (count % 2 == 0) {
			frameX++;
			if (frameX == 5) {
				count = 0;
				frameX = 0;
				bulletBlankTime = TIMEMANAGER->getWorldTime() + 2.0f;
			}
			else if (frameX == 3) {
				EBOSSBULLET tmp;
				tmp.point.x = position.x + 12;
				tmp.point.y = position.y + 130;
				tmp.rect = { tmp.point.x - 10, tmp.point.y - 14, tmp.point.x + 10, tmp.point.y + 14 };
				vBullet.push_back(tmp);
			}
		}
	}
	else { // idle상태
		action = EBOSSACTION_IDLE;
	}
}

void Enemy_BOSS::move()
{
	if (dogPosition->x >= position.x) {
		if (dogPosition->x - position.x <= 5.0f) {}
		else {
			position.x += speed;
			if (!SOUNDMANAGER->isPlaySound("bossMove") && !SOUNDMANAGER->isPlaySound("bossIntro")) {
				SOUNDMANAGER->play("bossMove", 1.0f * bgmSound);
			}
		}

		if (position.x >= 1250) position.x = 1250;
	}
	else {
		if (position.x - dogPosition->x <= 5.0f) {}
		else { 
			position.x -= speed;
			if (!SOUNDMANAGER->isPlaySound("bossMove") && !SOUNDMANAGER->isPlaySound("bossIntro")) {
				SOUNDMANAGER->play("bossMove", 1.0f * bgmSound);
			}
		}

		if (position.x <= 260) position.x = 260;
	}
}

void Enemy_BOSS::moveBullet()
{
	for (int i = 0; i < vBullet.size(); ++i) {
		vBullet.at(i).point.y += 10.0f;
		vBullet.at(i).rect.top += 10.0f;
		vBullet.at(i).rect.bottom += 10.0f;
		if (vBullet.at(i).rect.bottom >= CAMERAMANAGER->getAbsPosition({ 0, 1365 }).y) {
			viBullet = vBullet.begin();
			viBullet += i;
			vBullet.erase(viBullet);
			break;
		}
	}
}
