#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}

HRESULT Object::init(SOBJECT info, tstring MapName)
{
	time = 0;
	imageName = info.name;
	image tmp = *IMAGEMANAGER->findImage(MapName);
	position.x = info.x * tmp.getWidth();
	position.y = info.y * tmp.getHeight();
	tmp = *IMAGEMANAGER->findImage(imageName);
	rect = { position.x - tmp.getWidth() / 2, position.y - tmp.getHeight() / 2, position.x + tmp.getWidth() / 2, position.y + tmp.getHeight() / 2 };
	isTouch = false;
	if (imageName == L"escalator") {
		ANIMATIONMANAGER->start(imageName);
		rect = { position.x - tmp.getFrameWidth() / 2, position.y - tmp.getFrameHeight(), position.x + tmp.getFrameWidth() / 2,position.y};
	}
	else if(imageName == L"firePillar") {
		rect = { position.x - tmp.getFrameWidth() / 2, position.y - tmp.getFrameHeight() / 2, position.x + tmp.getFrameWidth() / 2, position.y + tmp.getFrameHeight() / 2 };
	}
	return S_OK;
}

void Object::release(void)
{
}

void Object::update(void)
{
	if (CheckCollisionRects(rect, *dogRect)) {
		isTouch = true;
	}
	else {
		isTouch = false;
	}
}

void Object::render(void)
{
	if (imageName == L"escalator") {
		IMAGEMANAGER->findImage(imageName)->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName));
	}
	else {
		IMAGEMANAGER->render(imageName, Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
}

void Object::deleteRect()
{
	dogMemory->deleteObjectRect(&rect);
}

HRESULT Object_TOOL::init(SOBJECT info, tstring MapName)
{
	Object::init(info, MapName);
	bool isOpen = false;
	return S_OK;
}

void Object_TOOL::release(void)
{
	Object::release();
}

void Object_TOOL::update(void)
{
	Object::update();
	if (!isOpen && isTouch) {
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
			isOpen = true;
			if (imageName == L"depot") {
				dogInvetory->push_back(EINVENITEN_CARD_USE);
				SOUNDMANAGER->play("event", 1.0f * effectSound);
				CAMERAMANAGER->textOut(L"유용한 도구를 얻었습니다");
			}
			else if (imageName == L"depot_boots") { 
				dogInvetory->push_back(EINVENITEN_BOOTS);
				SOUNDMANAGER->play("event", 1.0f * effectSound);
				CAMERAMANAGER->textOut(L"부츠를 얻었습니다");
			}
			else if (imageName == L"depot_card_white") {dogInvetory->push_back(EINVENITEN_CARD_WHITE);
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			CAMERAMANAGER->textOut(L"하얀카드를 얻었습니다");
			}
			else if (imageName == L"depot_card_red"){ dogInvetory->push_back(EINVENITEN_CARD_RED);
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			CAMERAMANAGER->textOut(L"빨강카드를 얻었습니다");
			}
			else if (imageName == L"depot_card_green") {dogInvetory->push_back(EINVENITEN_CARD_GREEN);
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			CAMERAMANAGER->textOut(L"초록카드를 얻었습니다");
			}
			else if (imageName == L"depot_card_blue"){ dogInvetory->push_back(EINVENITEN_CARD_BLUE);
			SOUNDMANAGER->play("event", 1.0f * effectSound);
			CAMERAMANAGER->textOut(L"파란카드를 얻었습니다");
			}
		}
	}
}

void Object_TOOL::render(void)
{
	if (isTouch) {
		IMAGEMANAGER->render(L"depot_active", Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
	else {
		IMAGEMANAGER->render(L"depot", Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
}

HRESULT Object_BOX::init(SOBJECT info, tstring MapName)
{
	Object::init(info, MapName);
	isBreak = false;
	pleaseDelete = false;
	for (int i = 0; i < 3; ++i) {
		dropItem[i] = (EDROPITEM)RND->getInt(4);
	}
	alpha = 1.0f;
	return S_OK;
}

void Object_BOX::release(void)
{
	Object::release();
}

void Object_BOX::update(void)
{
	Object::update();
	ifBreak();
	if (pleaseDelete) {
		Object::deleteRect();
		alpha -= 0.01f;
	}
}

void Object_BOX::render(void)
{
	if(pleaseDelete){
		IMAGEMANAGER->alphaRender(L"box_flag", Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, alpha);
	}
	else if (!isBreak) {
		Object::render();
	}
}

void Object_BOX::ifBreak()
{
	if (isBreak) {
		// 아이템떨구기

		SOUNDMANAGER->play("boxBreak", 1.0f * effectSound);
		for (int i = 0; i < 3; ++i) {
			DropItem* tmp;
			tmp = new DropItem;
			switch (dropItem[i])
			{
			case EDROPITEM_HEAL:
				tmp->init(EDROPITEM_HEAL, position.x - 10 + i * 10, position.y - 10 + i * 10);
				break;
			case EDROPITEM_MONEY:
				tmp->init(EDROPITEM_MONEY, position.x - 10 +i * 10, position.y - 10 + i * 10);
				break;
			case EDROPITEM_BULLET:
				tmp->init(EDROPITEM_BULLET, position.x - 10 + i * 10, position.y - 10 + i * 10);
				break;
			}
			tmp->setDogPosition(*dogMemory->getPoint());
			vDropsItem->push_back(tmp);
		}
		isBreak = false;
		pleaseDelete = true;
	}
}

HRESULT Object_DAMAGE::init(SOBJECT info, tstring MapName)
{
	Object::init(info, MapName);
	if (imageName == L"spike") damageRect = { rect.left + 5, rect.top, rect.right - 5, rect.bottom - 10 };
	else if (imageName == L"spike_up") damageRect = { rect.left + 5, rect.top - 10, rect.right - 5, rect.bottom};
	else if (imageName == L"spike_left") damageRect = { rect.left - 10, rect.top + 5, rect.right, rect.bottom - 5 };
	else if (imageName == L"spike_right") damageRect = { rect.left, rect.top + 5, rect.right - 10, rect.bottom - 5 };
	else if (imageName == L"press") {
		damageRect = { rect.left + 10,rect.bottom - 5, rect.right - 10, rect.bottom };
		isRoop = false;
		roopTime = 96 * 2;
	}
	else if (imageName == L"firePillar") {
		isRoop = false;
		roopTime = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(2, 4);
		damageRect = { 0, 0,0, 0 };
		count =0;
		frame=0;
	}
	else damageRect = rect;
	return S_OK;
}

void Object_DAMAGE::release(void)
{
}

void Object_DAMAGE::update(void)
{
	if (imageName == L"press") {
		if (CheckCollisionRects(damageRect, *dogRect)) {
			isTouch = true;
		}
		else {
			isTouch = false;
		}
		if (!isRoop) {
			roopTime -= 1;
			position.y -= 1;
			rect.top = position.y - 96 * 2 / 2;
			rect.bottom = position.y + 96 * 2 / 2;
			damageRect.top = rect.bottom - 5;
			damageRect.bottom = rect.bottom;
			if (roopTime == 32) {
				isRoop = true;
			}
		}
		else {
			roopTime += 8;
			position.y += 8;
			rect.top = position.y - 96 * 2 / 2;
			rect.bottom = position.y + 96 * 2 / 2;
			damageRect.top = rect.bottom - 5;
			damageRect.bottom = rect.bottom;
			if (roopTime == 96 * 2) {
				isRoop = false;
			}
		}
	}
	else if (imageName == L"firePillar") {
		if (!isRoop) {
			if (TIMEMANAGER->getWorldTime() >= roopTime) {
				isRoop = true;
				damageRect = { rect.left + 40, rect.top + 10, rect.right - 40,  rect.top + 10 };
				if (IsInRect(CAMERAMANAGER->getAbsPosition(position), D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM))) {
					SOUNDMANAGER->play("FireFlame", 1.0f * effectSound);
				}
			}
		}
		else { // (isRoop)
			if (damageRect.bottom <= rect.bottom) {
				damageRect.bottom+= 3.5f;
			}
			else {
				if (damageRect.top <= rect.bottom) {
					damageRect.top += 5.0f;
				}
			}
			if (CheckCollisionRects(damageRect, *dogRect)) {
				isTouch = true;
			}
			else {
				isTouch = false;
			}
			count++;
			if (count % 6 == 0) {
				frame++;
				if (frame == 15) {
					count = 0;
					frame = 0;
					damageRect = { 0, 0, 0, 0 };
					isRoop = false;
					roopTime = TIMEMANAGER->getWorldTime() + RND->getFromfloatTo(2, 4);
				}
			}
		}
	}
	else {
		Object::update();
	}
}

void Object_DAMAGE::render(void)
{
	if (imageName == L"press") {
		IMAGEMANAGER->render(imageName, Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, 62 * 2, roopTime);
		//D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).x, CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).y ,CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).x, CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).y }, Brush);
	}
	else if (imageName == L"firePillar") {
		if (isRoop) {
			IMAGEMANAGER->frameRender(imageName, Rt, frame, 0, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
			//IMAGEMANAGER->findImage(imageName)->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName));
			D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).x, CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).y ,CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).x, CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).y }, Brush);
		}
		else {
			IMAGEMANAGER->frameRender(imageName, Rt, 0, 0, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
			//D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).x, CAMERAMANAGER->getAbsPosition({ damageRect.left, damageRect.top }).y ,CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).x, CAMERAMANAGER->getAbsPosition({ damageRect.right, damageRect.bottom }).y }, Brush);
		}
	}
	else {
		IMAGEMANAGER->render(imageName, Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
}

HRESULT Object_ITEM::init(SOBJECT info, tstring MapName)
{
	Object::init(info, MapName);
	_isUse = false;
	return S_OK;
}

void Object_ITEM::release(void)
{
}

void Object_ITEM::update(void)
{
	Object::update();
	if (isTouch) {
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
			if (imageName == L"health") {
				dogMemory->useItem(0);
			}
			else if (imageName == L"upgrade") {
				dogMemory->useItem(1);
			}
			else if (imageName == L"bullet") {
				dogMemory->useItem(2);
			}
			_isUse = true;
		}
	}
}

void Object_ITEM::render(void)
{
	if (isTouch) {
		IMAGEMANAGER->render(imageName + L"_active", Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
	else {
		IMAGEMANAGER->render(imageName, Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y);
	}
}

HRESULT Object_VENDING::init(SOBJECT info, tstring MapName)
{
	Object::init(info, MapName);
	image tmp = *IMAGEMANAGER->findImage(MapName);
	position.y = info.y * tmp.getHeight() - 1;
	ANIMATIONMANAGER->start(imageName);
	ANIMATIONMANAGER->start(imageName + L"_active");
	tmp = *IMAGEMANAGER->findImage(imageName);
	rect = { position.x - tmp.getFrameWidth() / 2, position.y - tmp.getFrameHeight() / 2, position.x + tmp.getFrameWidth() / 2, position.y + tmp.getFrameHeight() / 2 };
	return S_OK;
}

void Object_VENDING::release(void)
{
}

void Object_VENDING::update(void)
{
	Object::update();
	if (isTouch) {
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
			if (imageName == L"healmachine") {
				if (*dogMemory->getAddreesMoney() >= 5) {
					*dogMemory->getAddreesMoney() -= 5;
					*dogMemory->getAddreescurrentHp() = *dogMemory->getAddreesMaxHp();
					CAMERAMANAGER->textOut(L"체력이 5만큼 증가했습니다");
					SOUNDMANAGER->play("event", 1.0f * effectSound);
				}
				else {
					CAMERAMANAGER->textOut(L"뮤타겐 5개가 필요합니다");
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
				}
			}
			else if (imageName == L"upgrademachine") {
				if (*dogMemory->getAddreesMoney() >= 5) {
					*dogMemory->getAddreesMoney() -= 5;
					dogMemory->getWeaponMemory()->aWeapon[dogMemory->getWeaponMemory()->currentWeapon].upgrade += 3;
					if (dogMemory->getWeaponMemory()->aWeapon[dogMemory->getWeaponMemory()->currentWeapon].upgrade >= UPGRADEMAX) {
						dogMemory->getWeaponMemory()->aWeapon[dogMemory->getWeaponMemory()->currentWeapon].upgrade = UPGRADEMAX;
					}
					CAMERAMANAGER->textOut(L"현재 무기 업그레이드");
					SOUNDMANAGER->play("event", 1.0f * effectSound);
				}
				else {
					CAMERAMANAGER->textOut(L"뮤타겐 5개가 필요합니다");
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
				}
			}
			else { //savemachine
				if (*dogMemory->getAddreesMoney() >= 5) {
					*dogMemory->getAddreesMoney() -= 5;
					sSaveData data = dogMemory->getSaveData();
					HANDLE file;
					DWORD write;
					tchar name[20];
					wsprintf(name, L"%d.save", saveDataNum);
					file = CreateFile(name,
						GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_ATTRIBUTE_NORMAL,
						NULL);
					WriteFile(file, &data, sizeof(sSaveData), &write, NULL);
					CloseHandle(file);
					CAMERAMANAGER->textOut(L"저장했습니다");
					SOUNDMANAGER->play("save", 1.0f * effectSound);
				}
				else {
					CAMERAMANAGER->textOut(L"뮤타겐 5개가 필요합니다");
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
				}
				
			}
		}
	}
}

void Object_VENDING::render(void)
{
	if (isTouch) {
		IMAGEMANAGER->findImage(imageName + L"_active")->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName + L"_active"));
	}
	else {
		IMAGEMANAGER->findImage(imageName)->aniRender(Rt, CAMERAMANAGER->getAbsPosition(position).x, CAMERAMANAGER->getAbsPosition(position).y, ANIMATIONMANAGER->findAnimation(imageName));
	}
}
