#include "stdafx.h"
#include "selectNewDataScene.h"


selectNewDataScene::selectNewDataScene()
{
}


selectNewDataScene::~selectNewDataScene()
{
}

HRESULT selectNewDataScene::init(void)
{
	if (!SOUNDMANAGER->isPlaySound("mainBGM")) {
		SOUNDMANAGER->play("mainBGM", 1.0f* bgmSound);
	}
	active = ESELECTACTIVE_NONE;
	excute = ESELECTACTIVE_NONE;

	for (int i = 0; i < 3; ++i) {
		dataFile[i] = { 0 };
	}
	for (int i = 1; i < 4; ++i) {
		tchar tmpStr[30];
		wsprintf(tmpStr, L"%d.save", i);
		if (_waccess_s(tmpStr, 0) == 0) {
			data[i - 1]._isExist = true;
		}
		else {
			data[i - 1]._isExist = false;
		}
	}

	for (int i = 1; i < 4; ++i) {
		if (data[i - 1]._isExist) {
			HANDLE file;
			DWORD read;
			tchar name[20];
			wsprintf(name, L"%d.save", i);
			file = CreateFile(name,
				GENERIC_READ,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
			ReadFile(file, &dataFile[i - 1], sizeof(sSaveData), &read, NULL);
			CloseHandle(file);
		}
	}
	return S_OK;
}

void selectNewDataScene::release(void)
{
}

void selectNewDataScene::update(void)
{
	if (IsInRect(_ptMouse, RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 50, 170, 38))) {
		active = ESELECTACTIVE_BACK;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ESELECTACTIVE_BACK;
		}
	}
	else if (IsInRect(_ptMouse, D2D1::RectF(301 + 288 * 0, 245, 301 + 288 * 0 + 180, 245 + 180))) {
		active = ESELECTACTIVE_DATA1;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ESELECTACTIVE_DATA1;
		}
	}
	else if (IsInRect(_ptMouse, D2D1::RectF(301 + 288 * 1, 245, 301 + 288 * 1 + 180, 245 + 180))) {
		active = ESELECTACTIVE_DATA2;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ESELECTACTIVE_DATA2;
		}
	}
	else if (IsInRect(_ptMouse, D2D1::RectF(301 + 288 * 2, 245, 301 + 288 * 2 + 180, 245 + 180))) {
		active = ESELECTACTIVE_DATA3;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
			excute = ESELECTACTIVE_DATA3;
		}
	}
	else {
		active = ESELECTACTIVE_NONE;
		excute = ESELECTACTIVE_NONE;
	}

	switch (excute)
	{
	case ESELECTACTIVE_DATA1:
		saveDataNum = 1;
		SCENEMANAGER->changeScene("levelSC");
		break;
	case ESELECTACTIVE_DATA2:
		saveDataNum = 2;
		SCENEMANAGER->changeScene("levelSC");
		break;
	case ESELECTACTIVE_DATA3:
		saveDataNum = 3;
		SCENEMANAGER->changeScene("levelSC");
		break;
	case ESELECTACTIVE_BACK:
		SCENEMANAGER->changeScene("menuSC");
		break;
	}
}

void selectNewDataScene::render(void)
{
	IMAGEMANAGER->render(L"choiceBG", Rt);
	IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기

	DWInit(L"함초롬돋움", 16, &WriteFactory, &TextFormat);
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	tchar tmpStr[10];
	swprintf_s(tmpStr, TEXT("새 로 하 기"));
	D2TextOut(Rt, tmpStr, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2, 200, 170, 250), AquablueBrush);

	for (int i = 1; i < 4; ++i) {
		if (data[i - 1]._isExist) {
			D2TextOut(Rt, dataFile[i - 1].time, TextFormat, D2D1::RectF(295 + 288 * (i - 1), 220, 295 + 188 + 288 * (i - 1), 220 + 20), AquablueBrush);
			IMAGEMANAGER->render(L"thePit", Rt, 301 + 288 * (i - 1), 245);
			D2TextOut(Rt, dataFile[i - 1].mapName, TextFormat, D2D1::RectF(295 + 288 * (i - 1), 430, 295 + 188 + 288 * (i - 1), 430 + 20), AquablueBrush);
		}
	}

	switch (active)
	{
	case ESELECTACTIVE_DATA1:
	case ESELECTACTIVE_DATA2:
	case ESELECTACTIVE_DATA3:
		Rt->FillRectangle(D2D1::RectF(301 + 288 * (active - 1), 245, 301 + 288 * (active - 1) + 180, 245 + 180), BlackBrush);
		break;
	case ESELECTACTIVE_BACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
		break;
	}

	switch (excute)
	{
	case ESELECTACTIVE_DATA1:
	case ESELECTACTIVE_DATA2:
	case ESELECTACTIVE_DATA3:
		D2Rectangle(Rt, D2D1::RectF(301 + 288 * (active - 1), 245, 301 + 288 * (active - 1) + 180, 245 + 180), BlackBrush);
		break;
	case ESELECTACTIVE_BACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
		break;
	}

	swprintf_s(tmpStr, TEXT("돌아가기"));
	D2TextOut(Rt, tmpStr, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 43, 170, 38), AquablueBrush);
}
