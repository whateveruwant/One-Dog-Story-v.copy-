#include "stdafx.h"
#include "UIManager.h"


UIManager::UIManager()
{
}


UIManager::~UIManager()
{
}

HRESULT UIManager::init(void)
{
	hpBar = new progressBar;
	hpBar->init(L"images/UI/ingame/HealthBar.png", 130, 18, 164, 18);
	upgradeBar = new progressBar;
	upgradeBar->init(L"images/UI/ingame/WeaponBar.png", 130, 48, 164, 18);
	return S_OK;
}

void UIManager::release(void)
{
	SAFE_DELETE(hpBar);
	SAFE_DELETE(upgradeBar);
}

void UIManager::update(void)
{
	hpBar->setGauge(*currentHP, *maxHP);
	if (dogWeapon->currentWeapon != EWEAPON_NONE) {
		upgradeBar->setGauge(dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade, UPGRADEMAX);
	}
}

void UIManager::render(void)
{
	IMAGEMANAGER->render(L"inventory", Rt);
	IMAGEMANAGER->render(L"dog_info", Rt);
	tchar tmpStr[20];
	wsprintf(tmpStr, L"%d / %d", *currentHP, *maxHP);
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(225, 18, 361, 38), AquablueBrush);
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	wsprintf(tmpStr, L"%d", *money);
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(133, 129, 171, 149), AquablueBrush);
	hpBar->render();
	//인벤토리
	for (int i = 0; i < dogInvetory->size(); ++i) {
		switch (dogInvetory->at(i))
		{
		case EINVENITEN_BOOTS:
			IMAGEMANAGER->render(L"boots", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		case EINVENITEN_CARD_RED:
			IMAGEMANAGER->render(L"redcard", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		case EINVENITEN_CARD_GREEN:
			IMAGEMANAGER->render(L"greencard", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		case EINVENITEN_CARD_BLUE:
			IMAGEMANAGER->render(L"bluecard", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		case EINVENITEN_CARD_WHITE:
			IMAGEMANAGER->render(L"whitecard", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		case EINVENITEN_CARD_USE:
			IMAGEMANAGER->render(L"tool", Rt, WINSIZEX_NUM / 2 - 225 + i * 50, WINSIZEY_NUM - 28);
			break;
		}
	}

	switch (dogWeapon->currentWeapon)
	{
	case EWEAPON_CLUP:
		IMAGEMANAGER->render(L"ui_club", Rt);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(306, 47, 366, 67), AquablueBrush);
		upgradeBar->render();
		break;
	case EWEAPON_GUN:
		IMAGEMANAGER->render(L"ui_gun", Rt);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].bulletNum);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(133, 93, 171, 113), AquablueBrush);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(306, 47, 366, 67), AquablueBrush);
		upgradeBar->render();
		break;
	case EWEAPON_SHOTGUN:
		IMAGEMANAGER->render(L"ui_shotgun", Rt);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].bulletNum);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(133, 93, 171, 113), AquablueBrush);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(306, 47, 366, 67), AquablueBrush);
		upgradeBar->render();
		break;
	case EWEAPON_ROCKET:
		IMAGEMANAGER->render(L"ui_rocket", Rt);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].bulletNum);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(133, 93, 171, 113), AquablueBrush);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(306, 47, 366, 67), AquablueBrush);
		upgradeBar->render();
		break;
	case EWEAPON_PLASMA:
		IMAGEMANAGER->render(L"ui_plasma", Rt);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].bulletNum);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(133, 93, 171, 113), AquablueBrush);
		wsprintf(tmpStr, L"%d", dogWeapon->aWeapon[dogWeapon->currentWeapon].upgrade);
		D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(306, 47, 366, 67), AquablueBrush);
		upgradeBar->render();
		break;
	}

	CAMERAMANAGER->render();
}
