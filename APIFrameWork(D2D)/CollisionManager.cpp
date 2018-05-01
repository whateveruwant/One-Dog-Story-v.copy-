#include "stdafx.h"
#include "CollisionManager.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

HRESULT CollisionManager::init(D2D_POINT_2F* posi, float width, float height, tstring mapName)
{
	charPo = posi;
	charWidth = width;
	charHeight = height;
	onView = false;
	updateRectPosi();

	load(mapName);
	currentMapName = mapName;
	return S_OK;
}

void CollisionManager::release(void)
{
}

void CollisionManager::update(tstring mapName)
{
	updateRectPosi();
	if (currentMapName != mapName) {
		load(mapName);
		currentMapName = mapName;
	}
	if (KEYMANAGER->isOnceKeyDown('P')) {
		onView = !onView;
	}
}

void CollisionManager::render(void)
{
	if (onView) {
		D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({body.left, body.top}).x, CAMERAMANAGER->getAbsPosition({ body.left, body.top }).y,CAMERAMANAGER->getAbsPosition({ body.right, body.bottom }).x, CAMERAMANAGER->getAbsPosition({ body.right, body.bottom }).y }, Brush); //body
		D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ headToBottom.left, headToBottom.top }).x, CAMERAMANAGER->getAbsPosition({ headToBottom.left, headToBottom.top }).y,CAMERAMANAGER->getAbsPosition({ headToBottom.right, headToBottom.bottom }).x, CAMERAMANAGER->getAbsPosition({ headToBottom.right, headToBottom.bottom }).y }, WhiteBrush); //head
		D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({ leftToRightArm.left, leftToRightArm.top }).x, CAMERAMANAGER->getAbsPosition({ leftToRightArm.left, leftToRightArm.top }).y,CAMERAMANAGER->getAbsPosition({ leftToRightArm.right, leftToRightArm.bottom }).x, CAMERAMANAGER->getAbsPosition({ leftToRightArm.right, leftToRightArm.bottom }).y }, WhiteBrush); //bottom
		
		//collisionLine
		for (int i = 0; i < lineNum; ++i) {
			LineMake(Rt, CAMERAMANAGER->getAbsPosition(line[i].postPoint).x, CAMERAMANAGER->getAbsPosition(line[i].postPoint).y, CAMERAMANAGER->getAbsPosition(line[i].endPoint).x, CAMERAMANAGER->getAbsPosition(line[i].endPoint).y, Brush);
		}
		for (int i = 0; i < rectNum; ++i) {
			D2Rectangle(Rt, { CAMERAMANAGER->getAbsPosition({rect[i].rect.left,rect[i].rect.top}).x, 
				CAMERAMANAGER->getAbsPosition({ rect[i].rect.left,rect[i].rect.top }).y,
				CAMERAMANAGER->getAbsPosition({ rect[i].rect.right,rect[i].rect.bottom }).x,
				CAMERAMANAGER->getAbsPosition({ rect[i].rect.right,rect[i].rect.bottom }).y }, BlueBrush);
		}
	}
}

void CollisionManager::updateRectPosi()
{
	body = { charPo->x - charWidth / 2, charPo->y - charHeight, charPo->x + charWidth / 2, charPo->y };
	headToBottom = { charPo->x - charWidth / 4, charPo->y - charHeight, charPo->x + charWidth / 4,  charPo->y };
	leftToRightArm = { charPo->x - charWidth / 2,  charPo->y - charHeight, charPo->x + charWidth / 2, charPo->y - 5};
}

bool CollisionManager::checkCollisionLeft()
{
	for (int i = 0; i < lineNum; ++i) {
		if (!IsInRect(line[i].postPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 }) && !IsInRect(line[i].endPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 })) continue; 
		float tmp = getAngle(line[i].postPoint.x, line[i].postPoint.y, line[i].endPoint.x, line[i].endPoint.y);
		if ((tmp >= 65.0 && tmp <= 115.0) || (tmp >= 245.0 && tmp <= 295.0) || (tmp >= 335.0 && tmp <= 25.0) || (tmp >= 155.0 && tmp <= 205.0)) {
			if (CollisionLineRect(line[i].postPoint, line[i].endPoint, { leftToRightArm.left,leftToRightArm.top, leftToRightArm.left + (leftToRightArm.right - leftToRightArm.left) / 2 ,leftToRightArm.bottom })) {
				return true;
			}
		}
	}

	//objectRect
	for (int i = 0; i < vObjectRect.size(); ++i) {
		if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->left, vObjectRect.at(i)->bottom }, { leftToRightArm.left,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
			return true;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->right, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom }, { leftToRightArm.left,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
			return true;
		}
		//else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->top }, { leftToRightArm.left,leftToRightArm.top, leftToRightArm.left + (leftToRightArm.right - leftToRightArm.left) / 2 ,leftToRightArm.bottom })) {
		//	return true;
		//}
		//else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->bottom }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom }, { leftToRightArm.left,leftToRightArm.top, leftToRightArm.left + (leftToRightArm.right - leftToRightArm.left) / 2 ,leftToRightArm.bottom })) {
		//	return true;
		//}
	}

	return false;
}

bool CollisionManager::checkCollisionRight()
{
	for (int i = 0; i < lineNum; ++i) {
		if (!IsInRect(line[i].postPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 }) && !IsInRect(line[i].endPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 })) continue;
		float tmp = getAngle(line[i].postPoint.x, line[i].postPoint.y, line[i].endPoint.x, line[i].endPoint.y);
		if ((tmp >= 65.0 && tmp <= 115.0) || (tmp >= 245.0 && tmp <= 295.0) || (tmp >= 335.0 && tmp <= 25.0) || (tmp >= 155.0 && tmp <= 205.0)) {
			if (CollisionLineRect(line[i].postPoint, line[i].endPoint, { leftToRightArm.right - (leftToRightArm.right - leftToRightArm.left) / 2,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom})) {
				return true;
			}
		}
	}

	//objectRect
	for (int i = 0; i < vObjectRect.size(); ++i) {
		if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->left, vObjectRect.at(i)->bottom },
		{ leftToRightArm.left,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
			return true;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->right, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		{ leftToRightArm.left,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
			return true;
		}
		//else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->top },
		//{ leftToRightArm.right - (leftToRightArm.right - leftToRightArm.left) / 2,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
		//	return true;
		//}
		//else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->bottom }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		//{ leftToRightArm.right - (leftToRightArm.right - leftToRightArm.left) / 2,leftToRightArm.top, leftToRightArm.right ,leftToRightArm.bottom })) {
		//	return true;
		//}
	}

	return false;
}

bool CollisionManager::checkCollisionTop()
{
	for (int i = 0; i < lineNum; ++i) {
		if (!IsInRect(line[i].postPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 }) && !IsInRect(line[i].endPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 })) continue;
		if (CollisionLineRect(line[i].postPoint, line[i].endPoint, { headToBottom.left, headToBottom.top, headToBottom.right, headToBottom.bottom - (headToBottom.bottom - headToBottom.top) / 2 })) {
			return true;
		}
	}

	//objectRect
	for (int i = 0; i < vObjectRect.size(); ++i) {
		if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->left, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top, headToBottom.right, headToBottom.bottom - (headToBottom.bottom - headToBottom.top) / 2 })) {
			return true;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->right, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top, headToBottom.right, headToBottom.bottom - (headToBottom.bottom - headToBottom.top) / 2 })) {
			return true;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->top },
		{ headToBottom.left, headToBottom.top, headToBottom.right, headToBottom.bottom - (headToBottom.bottom - headToBottom.top) / 2 })) {
			return true;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->bottom }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top, headToBottom.right, headToBottom.bottom - (headToBottom.bottom - headToBottom.top) / 2 })) {
			return true;
		}
	}

	return false;
}

float CollisionManager::checkCollisionBottom()
{
	for (int i = 0; i < lineNum; ++i) {
		//if (!IsInRect(line[i].postPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 }) && !IsInRect(line[i].endPoint, { charPo->x - 1000, charPo->y - 500, charPo->x + 1000, charPo->y + 500 })) continue;
		if (CollisionLineRect(line[i].postPoint, line[i].endPoint, { headToBottom.left, headToBottom.top + (headToBottom.bottom - headToBottom.top) / 2,headToBottom.right,headToBottom.bottom })) {
			float tmp = getAngle(line[i].postPoint.x, line[i].postPoint.y, line[i].endPoint.x, line[i].endPoint.y);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
	}

	//objectRect
	for (int i = 0; i < vObjectRect.size(); ++i) {
		if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->left, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top + (headToBottom.bottom - headToBottom.top) / 2,headToBottom.right,headToBottom.bottom })) {
			float tmp = getAngle(vObjectRect.at(i)->left, vObjectRect.at(i)->top, vObjectRect.at(i)->left, vObjectRect.at(i)->bottom);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->right, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top + (headToBottom.bottom - headToBottom.top) / 2,headToBottom.right,headToBottom.bottom })) {
			float tmp = getAngle(vObjectRect.at(i)->right, vObjectRect.at(i)->top, vObjectRect.at(i)->right, vObjectRect.at(i)->bottom);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->top }, { vObjectRect.at(i)->right, vObjectRect.at(i)->top },
		{ headToBottom.left, headToBottom.top + (headToBottom.bottom - headToBottom.top) / 2,headToBottom.right,headToBottom.bottom })) {
			float tmp = getAngle(vObjectRect.at(i)->left, vObjectRect.at(i)->top, vObjectRect.at(i)->right, vObjectRect.at(i)->top);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
		else if (CollisionLineRect({ vObjectRect.at(i)->left, vObjectRect.at(i)->bottom }, { vObjectRect.at(i)->right, vObjectRect.at(i)->bottom },
		{ headToBottom.left, headToBottom.top + (headToBottom.bottom - headToBottom.top) / 2,headToBottom.right,headToBottom.bottom })) {
			float tmp = getAngle(vObjectRect.at(i)->left, vObjectRect.at(i)->bottom, vObjectRect.at(i)->right, vObjectRect.at(i)->bottom);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
	}

	return 0.0f;
}

bool CollisionManager::checkCollisionHill()
{
	for (int i = 0; i < rectNum; ++i) {
		if (CheckCollisionRects(rect[i].rect, { body.left, body.bottom - 5 , body.right , body.bottom })) {
			return true;
		}
	}
	return false;
}

float CollisionManager::checkUserCollision(D2D_RECT_F rect)
{
	for (int i = 0; i < lineNum; ++i) {
		if (CollisionLineRect(line[i].postPoint, line[i].endPoint, rect)) {
			float tmp = getAngle(line[i].postPoint.x, line[i].postPoint.y, line[i].endPoint.x, line[i].endPoint.y);
			if (tmp == 0.0f) return 180.0f;
			else return tmp;
		}
	}
	return 0.0f;
}

void CollisionManager::load(tstring mapName)
{
	//충돌라인불러오기
	HANDLE file;
	DWORD read;
	tstring nameString = L"mapfile/" + mapName + L"_line.map";
	tchar* name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, line, sizeof(SCOLLILINE) * LINEMAX, &read, NULL);
	CloseHandle(file);
	image tmpBG  = *IMAGEMANAGER->findImage(mapName);
	for (int i = 0; i < LINEMAX; ++i) {
		if (line[i].state == EMAKELINE_NONE) {
			lineNum = i;
			break;
		}
		line[i].postPoint.x *= tmpBG.getWidth();
		line[i].postPoint.y *= tmpBG.getHeight();
		line[i].endPoint.x *= tmpBG.getWidth();
		line[i].endPoint.y *= tmpBG.getHeight();
	}

	nameString = L"mapfile/" + mapName + L"_rect.map";
	name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, rect, sizeof(SCOLLIRECT) * RECTMAX, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < RECTMAX; ++i) {
		if (rect[i].state == EMAKERECT_NONE) {
			rectNum = i;
			break;
		}
		rect[i].rect.left *= tmpBG.getWidth();
		rect[i].rect.right *= tmpBG.getWidth();
		rect[i].rect.top *= tmpBG.getHeight();
		rect[i].rect.bottom *= tmpBG.getHeight();
	}
}
