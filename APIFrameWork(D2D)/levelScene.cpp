#include "stdafx.h"
#include "levelScene.h"


levelScene::levelScene()
{
}


levelScene::~levelScene()
{
}

HRESULT levelScene::init(void)
{
	if (!SOUNDMANAGER->isPlaySound("mainBGM")) {
		SOUNDMANAGER->play("mainBGM", 1.0f * bgmSound);
	}
	state = ELEVELAVTIVE_NONE;
	excute = ELEVELAVTIVE_NONE;
	easy = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM/2 - 50, 170, 38);
	normal = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM/2, 170, 38);
	hard = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM/2 + 50, 170, 38);
	back = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 50, 170, 38);
	return S_OK;
}

void levelScene::release(void)
{
}

void levelScene::update(void)
{
	if (IsInRect(_ptMouse, easy)) {
		state = ELEVELAVTIVE_EASY;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ELEVELAVTIVE_EASY;
		}
	}
	else if (IsInRect(_ptMouse, normal)) {
		state = ELEVELAVTIVE_NORMAL;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ELEVELAVTIVE_NORMAL;
		}
	}
	else if (IsInRect(_ptMouse, hard)) {
		state = ELEVELAVTIVE_HARD;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ELEVELAVTIVE_HARD;
		}
	}
	else if (IsInRect(_ptMouse, back)) {
		state = ELEVELAVTIVE_BACK;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ELEVELAVTIVE_BACK;
		}
	}
	else {
		state = ELEVELAVTIVE_NONE;
	}

	switch (excute)
	{
	case ELEVELAVTIVE_EASY:
		level = 0;
		SCENEMANAGER->changeScene("mainGameSC");	
		break;
	case ELEVELAVTIVE_NORMAL:
		level = 1;
		SCENEMANAGER->changeScene("mainGameSC");		
		break;
	case ELEVELAVTIVE_HARD:
		level = 2;
		SCENEMANAGER->changeScene("mainGameSC");
		break;
	case ELEVELAVTIVE_BACK:
		SCENEMANAGER->changeScene("selectNewDataSC");
		break;
	}
}

void levelScene::render(void)
{
	IMAGEMANAGER->render(L"levelBG", Rt);

	IMAGEMANAGER->render(L"buttonNone", Rt, easy.left + (easy.right - easy.left) / 2, easy.top + (easy.bottom - easy.top) / 2);
	IMAGEMANAGER->render(L"buttonNone", Rt, normal.left + (normal.right - normal.left) / 2, normal.top + (normal.bottom - normal.top) / 2);
	IMAGEMANAGER->render(L"buttonNone", Rt, hard.left + (hard.right - hard.left) / 2, hard.top + (hard.bottom - hard.top) / 2);
	IMAGEMANAGER->render(L"buttonNone", Rt, back.left + (back.right - back.left) / 2, back.top + (back.bottom - back.top) / 2);

	switch (state)
	{
	case ELEVELAVTIVE_EASY:
		IMAGEMANAGER->render(L"buttonDown", Rt, easy.left + (easy.right - easy.left) / 2, easy.top + (easy.bottom - easy.top) / 2);
		break;
	case ELEVELAVTIVE_NORMAL:
		IMAGEMANAGER->render(L"buttonDown", Rt, normal.left + (normal.right - normal.left) / 2, normal.top + (normal.bottom - normal.top) / 2);
		break;
	case ELEVELAVTIVE_HARD:
		IMAGEMANAGER->render(L"buttonDown", Rt, hard.left + (hard.right - hard.left) / 2, hard.top + (hard.bottom - hard.top) / 2);
		break;
	case ELEVELAVTIVE_BACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, back.left + (back.right - back.left) / 2, back.top + (back.bottom - back.top) / 2);
		break;
	}

	switch (excute)
	{
	case ELEVELAVTIVE_EASY:
		IMAGEMANAGER->render(L"buttonUp", Rt, easy.left + (easy.right - easy.left) / 2, easy.top + (easy.bottom - easy.top) / 2);
		break;
	case ELEVELAVTIVE_NORMAL:
		IMAGEMANAGER->render(L"buttonUp", Rt, normal.left + (normal.right - normal.left) / 2, normal.top + (normal.bottom - normal.top) / 2);
		break;
	case ELEVELAVTIVE_HARD:
		IMAGEMANAGER->render(L"buttonUp", Rt, hard.left + (hard.right - hard.left) / 2, hard.top + (hard.bottom - hard.top) / 2);
		break;
	case ELEVELAVTIVE_BACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, back.left + (back.right - back.left) / 2, back.top + (back.bottom - back.top) / 2);
		break;
	}


	tchar tmpStr[20];
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	wsprintf(tmpStr, L"쉬 움");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(easy.left, easy.top + 10, easy.right, easy.bottom + 10), AquablueBrush);
	wsprintf(tmpStr, L"보 통");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(normal.left, normal.top + 10, normal.right, normal.bottom + 10), AquablueBrush);
	wsprintf(tmpStr, L"어려움");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(hard.left, hard.top + 10, hard.right, hard.bottom + 10), AquablueBrush);
	wsprintf(tmpStr, L"돌아가기");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(back.left, back.top + 10, back.right, back.bottom + 10), AquablueBrush);
}
