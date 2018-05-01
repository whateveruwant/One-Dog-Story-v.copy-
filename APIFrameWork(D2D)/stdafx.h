// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib, "dwrite.lib")	
#pragma comment(lib, "windowscodecs.lib")


#include "targetver.h"
#include <tchar.h>
#include <locale.h>


#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>


//Direct Header Files:
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>


// ���ֻ���ϴ� STL
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>


#ifdef UNICODE
typedef std::wstring tstring;
typedef wchar_t tchar;
#else
typedef std::string tstring;
typedef char tchar;
#endif


//==================================================================
//		## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//==================================================================
#include "util.h"
#include "commonMacroFunction.h"
#include "handyFunction.h"
#include "keyManager.h"
#include "timeManager.h"
#include "soundManager.h"
#include "sceneManager.h"
#include "imageManager.h"
#include "iniData.h"
#include "randomFunction.h"
#include "cameraManager.h"
#include "effectManager.h"
#include "animationManager.h"

//==================================================================
//		## �̱����� �߰��Ѵ� ##
//==================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define CAMERAMANAGER cameraManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define ANIMATIONMANAGER animationManager::getSingleton()

//==================================================================
//		## ���ӽ����̽� �߰��Ѵ� ##
//==================================================================
using namespace MY_UTIL;


//==================================================================
//		## �����ι� ## (������â �ʱ�ȭ)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("ONE DOG STORY"))
#define WINSTARTX 180
#define WINSTARTY 90
#define WINSIZEX_NUM 1280.f
#define WINSIZEY_NUM 720.f
#define WINSIZEX	static_cast<UINT>(ceil(WINSIZEX_NUM * dpiX / 94.9f))
#define WINSIZEY	static_cast<UINT>(ceil(WINSIZEY_NUM * dpiY / 91.3f))
#define WINSTYLE WS_CAPTION | WS_SYSMENU
#define LADDER_SPEED SPEED * 48 / 64
#define EFFECTSOUNDVOLUME 0.5f

typedef D2D_RECT_F RECTF;
typedef D2D1_ELLIPSE ELLIPSEF;
struct SGAMEKEYSETTING {
	tchar UP;
	tchar DOWN;
	tchar LEFT;
	tchar RIGHT;
	tchar JUMP;
	tchar USE;
	tchar BOXMOVE;
	tchar ATTACK;
	tchar FIDING;
	tchar NEXT;
	tchar BEFORE;
	tchar ZETPACK;
};

//==================================================================
//		## ��ũ���Լ� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); p = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] p; p = NULL;}}
#define SAFE_RELEASE(p)			{ if(p) { p->release(); p = NULL;} }


//==================================================================
//		## �������� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
//extern HINSTANCE _hInstance;
extern D2D_POINT_2F _ptMouse;
extern HWND hWnd;
extern ID2D1Factory* Factory;
extern ID2D1SolidColorBrush* Brush;
extern IDWriteFactory* WriteFactory;
extern IDWriteTextFormat* TextFormat;
extern IDWriteTextLayout* textLayout;
extern ID2D1HwndRenderTarget* Rt;
extern IWICImagingFactory *imagingFactory;
extern ID2D1BitmapRenderTarget* CRt;
extern ID2D1Bitmap* pBitmap;
extern ID2D1RadialGradientBrush* m_pRadialGradientBrush;
extern ID2D1SolidColorBrush* WhiteSmokeBrush;
extern ID2D1SolidColorBrush* BlackBrush;
extern ID2D1SolidColorBrush* WhiteBrush;
extern ID2D1SolidColorBrush* AquablueBrush;
extern ID2D1SolidColorBrush* BlueBrush;
extern ID2D1SolidColorBrush* RedBrush;
extern ID2D1SolidColorBrush* SolidRedBrush;
extern SGAMEKEYSETTING _mGameKey;
extern int saveDataNum;
extern int level;
extern float bgmSound;
extern float effectSound;
//==================================================================
//		## ���̷�Ʈ�� ##
//==================================================================
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif


#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif