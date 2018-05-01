#include "stdafx.h"
#include "helpScene.h"


helpScene::helpScene()
{
}


helpScene::~helpScene()
{
}

HRESULT helpScene::init(void)
{
	if (!SOUNDMANAGER->isPlaySound("mainBGM")) {
		SOUNDMANAGER->play("mainBGM", 1.0f * bgmSound);
	}
	onBack = false;
	goBack = false;
	activeMenu = EHELPACTIVEMENU_NONE;
	excuteMenu = EHELPEXCUTEMENU_NONE;
	return S_OK;
}

void helpScene::release(void)
{
}

void helpScene::update(void)
{
	if (excuteMenu == EHELPEXCUTEMENU_NONE) {
		if (IsInRect(_ptMouse, RectFMakeCenter(522, 194, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_JUMP;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_JUMP;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 238, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_LEFT;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_LEFT;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 282, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_RIGHT;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_RIGHT;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 326, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_UP;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_UP;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 370, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_DOWN;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_DOWN;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 414, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_USE;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_USE;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 458, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_MOVEBOX;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f);
				excuteMenu = EHELPEXCUTEMENU_MOVEBOX;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(522, 502, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_ATTACK;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_ATTACK;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(839, 194, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_FINDING;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_FINDING;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(839, 238, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_NEXT;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_NEXT;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(839, 282, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_BEFORE;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_BEFORE;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(839, 326, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_JETPACK;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_JETPACK;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 50, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_GOBACK;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_GOBACK;
			}
		}
		else if (IsInRect(_ptMouse, RectFMakeCenter(839, 326 + 44, 170, 38))) {
			activeMenu = EHELPACTIVEMENU_SOUND;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				SOUNDMANAGER->play("clickSound", 1.0f* effectSound);
				excuteMenu = EHELPEXCUTEMENU_SOUND;
			}
		}
		else activeMenu = EHELPACTIVEMENU_NONE;
	}
	else {
		switch (excuteMenu)
		{
		case EHELPEXCUTEMENU_JUMP:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.JUMP = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_LEFT:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.LEFT = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_RIGHT:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.RIGHT = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_UP:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.UP = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_DOWN:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.DOWN = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_USE:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.USE = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_MOVEBOX:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.BOXMOVE = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_ATTACK:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.ATTACK = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_FINDING:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.FIDING = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_NEXT:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.NEXT = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_BEFORE:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.BEFORE = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_JETPACK:
			for (int i = 0; i < 256; ++i) {
				if (i == 0xFF) break;
				if (GetAsyncKeyState(i) & 0x8000 && (GetAsyncKeyState(VK_LBUTTON) == 0x0000)) {
					if (i == VK_LBUTTON) continue;
					_mGameKey.ZETPACK = (tchar)i;
					excuteMenu = EHELPEXCUTEMENU_NONE;
					break;
				}
			}
			break;
		case EHELPEXCUTEMENU_SOUND:
			SCENEMANAGER->changeScene("soundSC");
			break;
		case EHELPEXCUTEMENU_GOBACK:
			SCENEMANAGER->changeScene("menuSC");
			break;
		}
	}
}

void helpScene::render(void)
{
	DWInit(L"함초롬돋움", 16, &WriteFactory, &TextFormat);
	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	wchar_t str[256];
	IMAGEMANAGER->render(L"helpBG", Rt);

	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 194); //점프 +43
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 238); //좌
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 282); //우
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 326); //상
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 370); //하
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 414); //사용하기
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 458); //뛰어넘기-박스
	IMAGEMANAGER->render(L"buttonNone", Rt, 522, 502); //공격-동의
	IMAGEMANAGER->render(L"buttonNone", Rt, 839, 194); //수색(후각)
	IMAGEMANAGER->render(L"buttonNone", Rt, 839, 238); //다음무기
	IMAGEMANAGER->render(L"buttonNone", Rt, 839, 282); //이전무기
	IMAGEMANAGER->render(L"buttonNone", Rt, 839, 326); //제트팩
	IMAGEMANAGER->render(L"buttonNone", Rt, 839, 326 + 44); //제트팩
	IMAGEMANAGER->render(L"buttonNone", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기

	switch (activeMenu)
	{
	case EHELPACTIVEMENU_JUMP:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 194); //점프 +43
		break;
	case EHELPACTIVEMENU_LEFT:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 238); //좌
		break;
	case EHELPACTIVEMENU_RIGHT:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 282); //우
		break;
	case EHELPACTIVEMENU_UP:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 326); //상
		break;
	case EHELPACTIVEMENU_DOWN:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 370); //하
		break;
	case EHELPACTIVEMENU_USE:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 414); //사용하기
		break;
	case EHELPACTIVEMENU_MOVEBOX:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 458); //뛰어넘기-박스
		break;
	case EHELPACTIVEMENU_ATTACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, 522, 502); //공격-동의
		break;
	case EHELPACTIVEMENU_FINDING:
		IMAGEMANAGER->render(L"buttonDown", Rt, 839, 194); //수색(후각)
		break;
	case EHELPACTIVEMENU_NEXT:
		IMAGEMANAGER->render(L"buttonDown", Rt, 839, 238); //다음무기
		break;
	case EHELPACTIVEMENU_BEFORE:
		IMAGEMANAGER->render(L"buttonDown", Rt, 839, 282); //이전무기
		break;
	case EHELPACTIVEMENU_JETPACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, 839, 326); //제트팩
		break;
	case EHELPACTIVEMENU_SOUND:
		IMAGEMANAGER->render(L"buttonDown", Rt, 839, 370); //제트팩
		break;
	case EHELPACTIVEMENU_GOBACK:
		IMAGEMANAGER->render(L"buttonDown", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
		break;
	}

	switch (excuteMenu)
	{
	case EHELPEXCUTEMENU_NONE:
		
		break;
	case EHELPEXCUTEMENU_JUMP:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 194); //점프 +43
		break;
	case EHELPEXCUTEMENU_LEFT:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 238); //좌
		break;
	case EHELPEXCUTEMENU_RIGHT:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 282); //우
		break;
	case EHELPEXCUTEMENU_UP:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 326); //상
		break;
	case EHELPEXCUTEMENU_DOWN:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 370); //하
		break;
	case EHELPEXCUTEMENU_USE:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 414); //사용하기
		break;
	case EHELPEXCUTEMENU_MOVEBOX:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 458); //뛰어넘기-박스
		break;
	case EHELPEXCUTEMENU_ATTACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, 522, 502); //공격-동의
		break;
	case EHELPEXCUTEMENU_FINDING:
		IMAGEMANAGER->render(L"buttonUp", Rt, 839, 194); //수색(후각)
		break;
	case EHELPEXCUTEMENU_NEXT:
		IMAGEMANAGER->render(L"buttonUp", Rt, 839, 238); //다음무기
		break;
	case EHELPEXCUTEMENU_BEFORE:
		IMAGEMANAGER->render(L"buttonUp", Rt, 839, 282); //이전무기
		break;
	case EHELPEXCUTEMENU_JETPACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, 839, 326); //제트팩
		break;
	case EHELPEXCUTEMENU_SOUND:
		IMAGEMANAGER->render(L"buttonUp", Rt, 839, 370); //제트팩
		break;
	case EHELPEXCUTEMENU_GOBACK:
		IMAGEMANAGER->render(L"buttonUp", Rt, WINSIZEX_NUM / 2, WINSIZEY_NUM - 50); //돌아가기
		break;
	}

	swprintf_s(str, TEXT("0x%X"), _mGameKey.JUMP);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 194 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.LEFT);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 238 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.RIGHT);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 282 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.UP);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 326 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.DOWN);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 370 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.USE);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 414 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.BOXMOVE);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 458 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.ATTACK);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(522, 502 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.FIDING);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(839, 194 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.NEXT);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(839, 238 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.BEFORE);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(839, 282 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("0x%X"), _mGameKey.ZETPACK);
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(839, 326 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("사운드"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(839, 370 + 7, 170, 38), AquablueBrush);
	swprintf_s(str, TEXT("돌아가기"));
	D2TextOut(Rt, str, TextFormat, RectFMakeCenter(WINSIZEX_NUM / 2, WINSIZEY_NUM - 43, 170, 38), AquablueBrush);
}