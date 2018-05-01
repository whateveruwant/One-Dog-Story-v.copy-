#include "stdafx.h"
#include "Elevator.h"


Elevator::Elevator()
{
}


Elevator::~Elevator()
{
}

HRESULT Elevator::init(SELEVATOR _Elevator, tstring MapName)
{
	image tmpBG = *IMAGEMANAGER->findImage(MapName);
	info.startX = _Elevator.startX* tmpBG.getWidth();
	info.startY = _Elevator.startY* tmpBG.getHeight();
	info.endX = _Elevator.endX* tmpBG.getWidth();
	info.endY = _Elevator.endY* tmpBG.getHeight();
	info.state = _Elevator.state;
	wsprintf(info.name, _Elevator.name);
	info.kind = _Elevator.kind;
	for (int i = 0; i < 2; ++i) {
		info.switchPosition[i].x = _Elevator.switchPosition[i].x * tmpBG.getWidth();
		info.switchPosition[i].y = _Elevator.switchPosition[i].y * tmpBG.getHeight();
	}
	isTouchSwitch = false;
	startToEnd = false;
	onLift = false;

	liftPosition = { info.startX, info.startY };

	liftImage = *IMAGEMANAGER->findImage(info.name);
	liftRect = { liftPosition.x - liftImage.getWidth()/2, liftPosition.y - liftImage.getHeight() / 2, liftPosition.x + liftImage.getWidth() / 2, liftPosition.y + liftImage.getHeight() / 2 };

	return S_OK;
}

void Elevator::release(void)
{
}

void Elevator::update(void)
{
	if (info.kind != EELEVATORKIND_LASER) {
		moveElevator();
		if (info.state == EMAKEELEVATOR_SWITCHSET1) {
			for (int i = 0; i < 1; ++i) {
				if (CheckCollisionRects({ info.switchPosition[i].x - 21, info.switchPosition[i].y - 31, info.switchPosition[i].x + 21, info.switchPosition[i].y + 31 }, *dogMemory->getRectMemory())) {
					isTouchSwitch = true;
					touchSwitch = i;
					break;
				}
				isTouchSwitch = false;
			}
		}
		else if (info.state == EMAKEELEVATOR_SWITCHSET2) {
			for (int i = 0; i < 2; ++i) {
				int a = 0;
				if (CheckCollisionRects({ info.switchPosition[i].x - 21, info.switchPosition[i].y - 31, info.switchPosition[i].x + 21, info.switchPosition[i].y + 31 }, *dogMemory->getRectMemory())) {
					isTouchSwitch = true;
					touchSwitch = i;
					break;
				}
				isTouchSwitch = false;
			}
		}

		if (isTouchSwitch) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				if (!SOUNDMANAGER->isPlaySound("elevatorStart")) {
					SOUNDMANAGER->play("elevatorStart", 1.0f * effectSound);
				}
				SOUNDMANAGER->play("switch", 1.0f * effectSound);
				startToEnd = !startToEnd;
				int a = 0;
			}
		}

		if (CheckCollisionRects(liftRect, *dogMemory->getRectMemory())) {
			onLift = true;
		}
		else onLift = false;
	}
	else { //laser
		for (int i = 0; i < 1; ++i) {
			if (CheckCollisionRects({ info.switchPosition[i].x - 21, info.switchPosition[i].y - 31, info.switchPosition[i].x + 21, info.switchPosition[i].y + 31 }, *dogMemory->getRectMemory())) {
				isTouchSwitch = true;
				touchSwitch = i;
				break;
			}
			isTouchSwitch = false;
		}
		if (isTouchSwitch) {
			if (KEYMANAGER->isOnceKeyDown(_mGameKey.USE)) {
				SOUNDMANAGER->play("switch", 1.0f * effectSound);
				startToEnd = !startToEnd;
			}
		}

		if (!startToEnd) { //레이저온
			if (CollisionLineRect({info.startX, info.startY}, { info.endX, info.endY }, *dogMemory->getRectMemory())) {
				onLift = true;
			}
			else onLift = false;

			if (IsInRect(CAMERAMANAGER->getAbsPosition(liftPosition), D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM))) {
				if (!SOUNDMANAGER->isPlaySound("laser")) {
					SOUNDMANAGER->play("laser", 1.0f * effectSound);
				}
			}
		}
		else { //레이저오프
			onLift = false;
			SOUNDMANAGER->stop("laser");
		}
	}
}

void Elevator::render(void)
{
	if (info.state == EMAKEELEVATOR_SWITCHSET1) {
		IMAGEMANAGER->render(L"panel", Rt, CAMERAMANAGER->getAbsPosition(info.switchPosition[0]).x, CAMERAMANAGER->getAbsPosition(info.switchPosition[0]).y);
	}
	else if (info.state == EMAKEELEVATOR_SWITCHSET2) {
		IMAGEMANAGER->render(L"panel", Rt, CAMERAMANAGER->getAbsPosition(info.switchPosition[0]).x, CAMERAMANAGER->getAbsPosition(info.switchPosition[0]).y);
		IMAGEMANAGER->render(L"panel", Rt, CAMERAMANAGER->getAbsPosition(info.switchPosition[1]).x, CAMERAMANAGER->getAbsPosition(info.switchPosition[1]).y);
	}
	if (isTouchSwitch) {
		IMAGEMANAGER->render(L"panel_active", Rt, CAMERAMANAGER->getAbsPosition(info.switchPosition[touchSwitch]).x, CAMERAMANAGER->getAbsPosition(info.switchPosition[touchSwitch]).y);
	}
	if (!startToEnd  && info.kind == EELEVATORKIND_LASER) {
		Rt->FillRectangle({ CAMERAMANAGER->getAbsPosition({ info.startX, info.startY }).x, CAMERAMANAGER->getAbsPosition({ info.startX, info.startY }).y - 3, CAMERAMANAGER->getAbsPosition({ info.endX, info.endY }).x, CAMERAMANAGER->getAbsPosition({ info.endX, info.endY }).y +3}, SolidRedBrush);
	}
	IMAGEMANAGER->render(info.name, Rt, CAMERAMANAGER->getAbsPosition(liftPosition).x, CAMERAMANAGER->getAbsPosition(liftPosition).y);
}

void Elevator::moveElevator()
{
	if (startToEnd) {
		float distance = getDistance(liftPosition.x, liftPosition.y, info.endX, info.endY);
		if (KEYMANAGER->isOnceKeyDown('L')) {
			int a = 0;


		}
		if (distance <= 2.0f) {
			if (SOUNDMANAGER->isPlaySound("elevatorStart")) {
				//SOUNDMANAGER->stop("elevatorloop");
				SOUNDMANAGER->stop("elevatorStart");
	 			SOUNDMANAGER->play("elevatorEnd");
			}
			liftPosition.x = info.endX;
			liftPosition.y = info.endY;
		}
		else {
			float angle = getAngle(liftPosition.x, liftPosition.y, info.endX, info.endY);
			if (!SOUNDMANAGER->isPlaySound("elevatorStart")) {
				if (!SOUNDMANAGER->isPlaySound("elevatorloop")) {
					//SOUNDMANAGER->play("elevatorloop", 1.0f * effectSound);
				}
			}
			if (onLift && sinf(angle * (PI / 180)) * 3.0f <= 0) {
				dogMemory->modifyY(-sinf(angle * (PI / 180)) * 3.0f);
				dogMemory->modifyX(cosf(angle * (PI / 180)) * 3.0f);
			}
			liftPosition.x += cosf(angle * (PI / 180)) * 3.0f;
			liftPosition.y -= sinf(angle * (PI / 180)) * 3.0f;
		}
	}
	else {
		float distance = getDistance(liftPosition.x, liftPosition.y, info.startX, info.startY);
		if (distance <= 2.0f) {
			if (SOUNDMANAGER->isPlaySound("elevatorStart")) {
				//SOUNDMANAGER->stop("elevatorloop");
				SOUNDMANAGER->stop("elevatorStart");
				SOUNDMANAGER->play("elevatorEnd");
			}
			liftPosition.x = info.startX;
			liftPosition.y = info.startY;
		}
		else {
			float angle = getAngle(liftPosition.x, liftPosition.y, info.startX, info.startY);
			if (!SOUNDMANAGER->isPlaySound("elevatorStart")) {
				if (!SOUNDMANAGER->isPlaySound("elevatorloop")) {
					//SOUNDMANAGER->play("elevatorloop", 1.0f * effectSound);
				}
			}
			if (onLift && sinf(angle * (PI / 180)) * 3.0f <= 0) {
				dogMemory->modifyY(-sinf(angle * (PI / 180)) * 3.0f);
				dogMemory->modifyX(cosf(angle * (PI / 180)) * 3.0f);
			}
			liftPosition.x += cosf(angle * (PI / 180)) * 3.0f;
			liftPosition.y -= sinf(angle * (PI / 180)) * 3.0f;
		}
	}
	liftRect = { liftPosition.x - liftImage.getWidth() / 2, liftPosition.y - liftImage.getHeight() / 2, liftPosition.x + liftImage.getWidth() / 2, liftPosition.y + liftImage.getHeight() / 2 };
}

void Elevator::deleteRect()
{
	dogMemory->deleteObjectRect(&liftRect);
}