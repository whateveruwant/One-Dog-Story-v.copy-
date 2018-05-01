#include "stdafx.h"
#include "Door.h"


Door::Door()
{
}


Door::~Door()
{
}

HRESULT Door::init(SDOOR _door, tstring MapName)
{
	wsprintf(info.destination, _door.destination);
	image tmpBG = *IMAGEMANAGER->findImage(MapName);
	info.kind = _door.kind;
	info.x = _door.x * tmpBG.getWidth();
	info.y = _door.y * tmpBG.getHeight();

	tstring nextMapName = _door.destination;
	info.dsX = _door.dsX;
	info.dsY = _door.dsY;

	canOpen = false;
	active = false;
	goChangeMap = false;
	opening = false;
	rect = RectMakeCenter(info.x, info.y, 112, 106);
	return S_OK;
}

void Door::release(void)
{
}

void Door::update(void)
{
	getActive();
	GoChangeMap();
	checkCanOpen();
	if (opening && !ANIMATIONMANAGER->findAnimation(L"DoorOpen")->isPlay()) {
		goChangeMap = true;
	}
}

void Door::render(void)
{
	switch (info.kind)
	{
	case EDOORKIND_NEED_OBJECT:
		if (active) {
			if (canOpen) {
				IMAGEMANAGER->render(L"vent_open_active", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
			else {
				IMAGEMANAGER->render(L"vent_close_active", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
		}
		else {
			if (canOpen) {
				IMAGEMANAGER->render(L"vent_open_idle", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
			else {
				IMAGEMANAGER->render(L"vent_close_idle", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
		}
		break;
	default:
		if (info.kind == EDOORKIND_BREAK) {
			if (active) {
				IMAGEMANAGER->render(L"door_break_active", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
			else {
				IMAGEMANAGER->render(L"door_break_idle", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
			}
		}
		else {
			if (opening) {
				IMAGEMANAGER->findImage(L"door_opening")->aniRender(Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y, ANIMATIONMANAGER->findAnimation(L"DoorOpen"));
			}
			else {
				if (active) {
					IMAGEMANAGER->render(L"door_active", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
				}
				else {
					IMAGEMANAGER->render(L"door_idle", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
				}
			}
		}
		break;
	}
}

void Door::GoChangeMap()
{
	if (active && canOpen) {
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
			switch (info.kind)
			{
			case EDOORKIND_NEED_OBJECT:
				goChangeMap = true;
				break;
			default:
				SOUNDMANAGER->play("door", 1.0f * effectSound);
				ANIMATIONMANAGER->start(L"DoorOpen");
				opening = true;
				break;
			}
		}
	}
}

void Door::getActive()
{
	if (CheckCollisionRects(rect, *dogInfo.dogRect)) {
		active = true;
	}
	else {
		active = false;
	}
}

void Door::checkCanOpen()
{
	switch (info.kind)
	{
	case EDOORKIND_BREAK:
		canOpen = false;
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				SOUNDMANAGER->play("textOut", 1.0f * effectSound);
				CAMERAMANAGER->textOut(L"고 장");
			}
		}
		break;
	case EDOORKIND_FREE:
		canOpen = true;
		break;
	case EDOORKIND_NEED_RED:
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				for (int i = 0; i < dogInfo.dogInvetory->size(); ++i) {
					if (dogInfo.dogInvetory->at(i) == EINVENITEN_CARD_RED) {
						vector<EINVENITEM>::iterator viTmp = dogInfo.dogInvetory->begin();
						viTmp += i;
						dogInfo.dogInvetory->erase(viTmp);
						canOpen = true;
						SOUNDMANAGER->play("textOut", 1.0f * effectSound);
						CAMERAMANAGER->textOut(L"열렸습니다");
						break;
					}
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
					CAMERAMANAGER->textOut(L"빨강카드가 필요합니다");
				}
			}
		}
		break;
	case EDOORKIND_NEED_BLUE:
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				for (int i = 0; i < dogInfo.dogInvetory->size(); ++i) {
					if (dogInfo.dogInvetory->at(i) == EINVENITEN_CARD_BLUE) {
						vector<EINVENITEM>::iterator viTmp = dogInfo.dogInvetory->begin();
						viTmp += i;
						dogInfo.dogInvetory->erase(viTmp);
						canOpen = true;
						SOUNDMANAGER->play("textOut", 1.0f * effectSound);
						CAMERAMANAGER->textOut(L"열렸습니다");
						break;
					}
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
					CAMERAMANAGER->textOut(L"파랑카드가 필요합니다");
				}
			}
		}
		break;
	case EDOORKIND_NEED_GREEN:
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				for (int i = 0; i < dogInfo.dogInvetory->size(); ++i) {
					if (dogInfo.dogInvetory->at(i) == EINVENITEN_CARD_GREEN) {
						vector<EINVENITEM>::iterator viTmp = dogInfo.dogInvetory->begin();
						viTmp += i;
						dogInfo.dogInvetory->erase(viTmp);
						canOpen = true;
						SOUNDMANAGER->play("textOut", 1.0f * effectSound);
						CAMERAMANAGER->textOut(L"열렸습니다");
						break;
					}
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
					CAMERAMANAGER->textOut(L"초록카드가 필요합니다");
				}
			}
		}
		break;
	case EDOORKIND_NEED_WHITE:
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				for (int i = 0; i < dogInfo.dogInvetory->size(); ++i) {
					if (dogInfo.dogInvetory->at(i) == EINVENITEN_CARD_WHITE) {
						vector<EINVENITEM>::iterator viTmp = dogInfo.dogInvetory->begin();
						viTmp += i;
						dogInfo.dogInvetory->erase(viTmp);
						canOpen = true;
						SOUNDMANAGER->play("textOut", 1.0f * effectSound);
						CAMERAMANAGER->textOut(L"열렸습니다");
						break;
					}
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
					CAMERAMANAGER->textOut(L"하얀카드가 필요합니다");
				}
			}
		}
		break;
	case EDOORKIND_NEED_OBJECT:
		if (active) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				for (int i = 0; i < dogInfo.dogInvetory->size(); ++i) {
					if (dogInfo.dogInvetory->at(i) == EINVENITEN_CARD_USE) {
						vector<EINVENITEM>::iterator viTmp = dogInfo.dogInvetory->begin();
						viTmp += i;
						dogInfo.dogInvetory->erase(viTmp);
						canOpen = true;
						SOUNDMANAGER->play("textOut", 1.0f * effectSound);
						CAMERAMANAGER->textOut(L"열렸습니다");
						break;
					}
					SOUNDMANAGER->play("textOut", 1.0f * effectSound);
					CAMERAMANAGER->textOut(L"도구가 필요합니다");
				}
			}
		}
		break;
	}
}