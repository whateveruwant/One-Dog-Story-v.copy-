#include "stdafx.h"
#include "mainGameAgainScene.h"


mainGameAgainScene::mainGameAgainScene()
{
}


mainGameAgainScene::~mainGameAgainScene()
{
}

HRESULT mainGameAgainScene::init(void)
{
	if (SOUNDMANAGER->isPlaySound("mainBGM")) {
		SOUNDMANAGER->stop("mainBGM");
	}
	if (!SOUNDMANAGER->isPlaySound("gameBGM2")) {
		SOUNDMANAGER->play("gameBGM2", 1.0f * bgmSound);
	}
	sSaveData tmpData;
	HANDLE file;
	DWORD read;
	tchar name[20];
	wsprintf(name, L"%d.save", saveDataNum);
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, &tmpData, sizeof(sSaveData), &read, NULL);
	CloseHandle(file);

	tstring mapName = tmpData.mapName;

	map = new Map;
	map->init(mapName);
	map->loadSaveData(tmpData);
	popupInit();
	return S_OK;
}

void mainGameAgainScene::release(void)
{
	SAFE_DELETE(map);
}

void mainGameAgainScene::update(void)
{
	if (!popUp) {
		map->update();
		CAMERAMANAGER->update();
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
			popUp = true;
		}
	}
	else { //팝업일때
		popupUpdate();
	}
}

void mainGameAgainScene::render(void)
{
	map->render();
	if (popUp) {
		popupRender();
	}
}

void mainGameAgainScene::popupInit()
{
	popUp = false;
	state = EPOPUPACTIVE_NONE;
	excute = EPOPUPACTIVE_NONE;
	bBack = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM / 2 - 18 - 10, 170, 38);
	bLoad = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM / 2 - 18 - 10 + 60, 170, 38);
	bOut = RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM / 2 - 18 - 10 + 60 * 2, 170, 38);
}

void mainGameAgainScene::popupUpdate()
{
	if (IsInRect(_ptMouse, bBack)) {
		state = EPOPUPACTIVE_BACK;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			excute = EPOPUPACTIVE_BACK;
		}
	}
	else if (IsInRect(_ptMouse, bLoad)) {
		state = EPOPUPACTIVE_LOAD;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			excute = EPOPUPACTIVE_LOAD;
		}
	}
	else if (IsInRect(_ptMouse, bOut)) {
		state = EPOPUPACTIVE_OUT;
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			excute = EPOPUPACTIVE_OUT;
		}
	}
	else {
		state = EPOPUPACTIVE_NONE;
	}

	switch (excute)
	{
	case EPOPUPACTIVE_BACK:
		popUp = false;
		excute = EPOPUPACTIVE_NONE;
		break;
	case EPOPUPACTIVE_LOAD: {
		SAFE_DELETE(map);
		sSaveData tmpData;
		HANDLE file;
		DWORD read;
		tchar name[20];
		wsprintf(name, L"%d.save", saveDataNum);
		file = CreateFile(name,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		ReadFile(file, &tmpData, sizeof(sSaveData), &read, NULL);
		CloseHandle(file);
		tstring mapName = tmpData.mapName;
		map = new Map;
		map->init(mapName);
		map->loadSaveData(tmpData);
		popUp = false;
		excute = EPOPUPACTIVE_NONE;
	}break;
	case EPOPUPACTIVE_OUT:
		SCENEMANAGER->changeScene("menuSC");
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		popUp = false;
	}
}

void mainGameAgainScene::popupRender()
{
	Rt->FillRectangle(D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM), BlackBrush);
	IMAGEMANAGER->render(L"popUp", Rt);

	IMAGEMANAGER->render(L"buttonNone", Rt, bBack.left + (bBack.right - bBack.left) / 2, bBack.top + (bBack.bottom - bBack.top) / 2);
	IMAGEMANAGER->render(L"buttonNone", Rt, bLoad.left + (bLoad.right - bLoad.left) / 2, bLoad.top + (bLoad.bottom - bLoad.top) / 2);
	IMAGEMANAGER->render(L"buttonNone", Rt, bOut.left + (bOut.right - bOut.left) / 2, bOut.top + (bOut.bottom - bOut.top) / 2);

	switch (state)
	{
	case EPOPUPACTIVE_NONE:
		break;
	case EPOPUPACTIVE_BACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, bBack.left + (bBack.right - bBack.left) / 2, bBack.top + (bBack.bottom - bBack.top) / 2);
		break;
	case EPOPUPACTIVE_LOAD:
		IMAGEMANAGER->render(L"buttonDown", Rt, bLoad.left + (bLoad.right - bLoad.left) / 2, bLoad.top + (bLoad.bottom - bLoad.top) / 2);
		break;
	case EPOPUPACTIVE_OUT:
		IMAGEMANAGER->render(L"buttonDown", Rt, bOut.left + (bOut.right - bOut.left) / 2, bOut.top + (bOut.bottom - bOut.top) / 2);
		break;
	}
	switch (excute)
	{
	case EPOPUPACTIVE_NONE:
		break;
	case EPOPUPACTIVE_BACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, bBack.left + (bBack.right - bBack.left) / 2, bBack.top + (bBack.bottom - bBack.top) / 2);
		break;
	case EPOPUPACTIVE_LOAD:
		IMAGEMANAGER->render(L"buttonUp", Rt, bLoad.left + (bLoad.right - bLoad.left) / 2, bLoad.top + (bLoad.bottom - bLoad.top) / 2);
		break;
	case EPOPUPACTIVE_OUT:
		IMAGEMANAGER->render(L"buttonUp", Rt, bOut.left + (bOut.right - bOut.left) / 2, bOut.top + (bOut.bottom - bOut.top) / 2);
		break;
	}

	tchar tmpStr[20];
	wsprintf(tmpStr, L"게임으로 돌아가기");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(bBack.left, bBack.top + 10, bBack.right, bBack.bottom + 10), AquablueBrush);
	wsprintf(tmpStr, L"게임 불러오기");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(bLoad.left, bLoad.top + 10, bLoad.right, bLoad.bottom + 10), AquablueBrush);
	wsprintf(tmpStr, L"나 가 기");
	D2TextOut(Rt, tmpStr, TextFormat, D2D1::RectF(bOut.left, bOut.top + 10, bOut.right, bOut.bottom + 10), AquablueBrush);
}
