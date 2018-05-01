#include "stdafx.h"
#include "soundScene.h"


soundScene::soundScene()
{
}


soundScene::~soundScene()
{
}

HRESULT soundScene::init(void)
{
	state = ESOUNDACTION_NONE;
	action = ESOUNDACTION_NONE;

	back = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 50, 170, 38);

	effectRect = RectFMakeCenter(558 + 162 * effectSound, 345, 10, 20);
	bgmRect = RectFMakeCenter(558 + 162 * bgmSound, 289, 10, 20);
	return S_OK;
}

void soundScene::release(void)
{
}

void soundScene::update(void)
{
	if (IsInRect(_ptMouse, bgmRect)) {
		state = ESOUNDACTION_BGM;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			action = ESOUNDACTION_BGM;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			action = ESOUNDACTION_NONE;
		}
	}
	else if (IsInRect(_ptMouse, effectRect)) {
		state = ESOUNDACTION_EFFECT;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			action = ESOUNDACTION_EFFECT;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			action = ESOUNDACTION_NONE;
		}
	}
	else if (IsInRect(_ptMouse, back)) {
		state = ESOUNDACTION_BACK;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			action = ESOUNDACTION_BACK;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			action = ESOUNDACTION_NONE;
		}
	}
	else {
		state = ESOUNDACTION_NONE;
		action = ESOUNDACTION_NONE;
	}

	switch (action)
	{
	case ESOUNDACTION_BGM:
		if (_ptMouse.x >= 558 && _ptMouse.x <= 720) {
			bgmRect = RectFMakeCenter(_ptMouse.x, 289, 10, 20);
		}
		break;
	case ESOUNDACTION_EFFECT:
		if (_ptMouse.x >= 558 && _ptMouse.x <= 720) {
			effectRect = RectFMakeCenter(_ptMouse.x, 345, 10, 20);
		}
		break;
	case ESOUNDACTION_BACK:
		bgmSound = (bgmRect.left + 5 - 558) / 162;
		effectSound = (effectRect.left + 5 - 558) / 162;
		SOUNDMANAGER->allsoundStop();
		SCENEMANAGER->changeScene("menuSC");
		break;
	}
}

void soundScene::render(void)
{
	IMAGEMANAGER->render(L"soundBG", Rt);

	IMAGEMANAGER->render(L"music", Rt, bgmRect.left, bgmRect.top); //bgm
	IMAGEMANAGER->render(L"music", Rt, effectRect.left, effectRect.top); //effect


	IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기

	if (state == ESOUNDACTION_BACK) {
		IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
	}

	if (action == ESOUNDACTION_BACK) {
		IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
	}

	tchar tmpStr[20];
	DWInit(L"함초롬돋움", 16, &WriteFactory, &TextFormat);
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	swprintf_s(tmpStr, TEXT("돌아가기"));
	D2TextOut(Rt, tmpStr, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 43, 170, 38), AquablueBrush);
}
