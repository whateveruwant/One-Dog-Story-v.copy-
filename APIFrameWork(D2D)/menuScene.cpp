#include "stdafx.h"
#include "menuScene.h"


menuScene::menuScene()
{
}


menuScene::~menuScene()
{
}


HRESULT menuScene::init(void) {
	SOUNDMANAGER->allsoundStop();
	if (!SOUNDMANAGER->isPlaySound("mainBGM")) {
		SOUNDMANAGER->play("mainBGM", 1.0f * bgmSound);
	}
	state = EMENUDOWN_NONE;
	excute = EMENUUP_NONE;
	return S_OK;
}

void menuScene::release(void) {

}

void menuScene::update(void) {
	bool isIn = false;
	for (int i = 0; i < 4; ++i) {
		if (IsInRect(_ptMouse, RectFMakeCenter(WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43, 170, 38))) {
			state = (EMENUDOWN)(i + 1);
			isIn = true;
			clickMouse();
			break;
		}
	}
	if (!isIn) state = EMENUDOWN_NONE;
}

void menuScene::render(void) {
	IMAGEMANAGER->render(L"mainmenuBG", Rt);
	buttonRender();

	//글자
	DWInit(L"함초롬돋움", 16, &WriteFactory, &TextFormat);
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	wchar_t str[256];
	swprintf_s(str, TEXT("새 게임"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2 - 1, WINSIZEY_NUM / 2 + 28, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("계속하기"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2 - 1, WINSIZEY_NUM / 2 + 28 + 1 * 43, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("설정"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2 - 1, WINSIZEY_NUM / 2 + 28 + 2 * 43, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("종료"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2 - 1, WINSIZEY_NUM / 2 + 28 + 3 * 43, 170, 38), AquablueBrush);
}

void menuScene::clickMouse()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		switch (state)
		{
		case EMENUDOWN_NEWGAME:
			excute = EMENUUP_NEWGAME;
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			SCENEMANAGER->changeScene("selectNewDataSC");
			break;
		case EMENUDOWN_CONTINUE:
			excute = EMENUUP_CONTINUE;
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			SCENEMANAGER->changeScene("selectDataSC");
			break;
		case EMENUDOWN_HELP:
			excute = EMENUUP_HELP;
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			SCENEMANAGER->changeScene("helpSC");
			break;
		case EMENUDOWN_EXIT:
			excute = EMENUUP_EXIT;
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			PostQuitMessage(0);
			break;
		}
	}
}

void menuScene::buttonRender()
{
	if (excute == EMENUUP_NONE) {
		switch (state)
		{
		case EMENUDOWN_NONE:
			for (int i = 0; i < 4; ++i) {
				IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUDOWN_NEWGAME:
			for (int i = 0; i < 4; ++i) {
				if (i == 0) IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUDOWN_CONTINUE:
			for (int i = 0; i < 4; ++i) {
				if (i == 1) IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUDOWN_HELP:
			for (int i = 0; i < 4; ++i) {
				if (i == 2) IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUDOWN_EXIT:
			for (int i = 0; i < 4; ++i) {
				if (i == 3) IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		}
	}
	else {
		switch (excute)
		{
		case EMENUUP_NEWGAME:
			for (int i = 0; i < 4; ++i) {
				if (i == 3) IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUUP_CONTINUE:
			for (int i = 0; i < 4; ++i) {
				if (i == 3) IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUUP_HELP:
			for (int i = 0; i < 4; ++i) {
				if (i == 3) IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		case EMENUUP_EXIT:
			for (int i = 0; i < 4; ++i) {
				if (i == 3) IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
				else IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2 + 1, WINSIZEY_NUM / 2 + 20 + i * 43);
			}
			break;
		}
	}
}