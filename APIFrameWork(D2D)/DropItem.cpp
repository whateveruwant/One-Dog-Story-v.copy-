#include "stdafx.h"
#include "DropItem.h"


HRESULT DropItem::init(EDROPITEM _kind, float x, float y)
{
	info._kind = _kind;
	info.x = x;
	info.y = y;
	return S_OK;
}

void DropItem::release(void)
{
}

void DropItem::update(void)
{
	float angle = getAngle(info.x, info.y, (*dogPo).x, (*dogPo).y - 30);
	info.x += cosf(angle * PI / 180)* 5.5f;
	info.y -= sinf(angle * (PI / 180)) * 5.5f;
}

void DropItem::render(void)
{
	switch (info._kind)
	{
	case EDROPITEM_HEAL:
		IMAGEMANAGER->render(L"bone", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
		break;
	case EDROPITEM_MONEY:
		IMAGEMANAGER->render(L"money", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
		break;
	case EDROPITEM_BULLET:
		IMAGEMANAGER->render(L"ammo", Rt, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).x, CAMERAMANAGER->getAbsPosition({ info.x, info.y }).y);
		break;
	}
}