#include "stdafx.h"
#include "timeManager.h"
timeManager::timeManager()
{
}
timeManager::~timeManager()
{
}
//==================================================================
//		## 생성자와 소멸자는 더이상 사용하지 않는다 ##
//==================================================================

HRESULT timeManager::init(void)
{
	//타이머 클래스 초기화
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)
{
	//타이머 클래스가 있으면 해제한다
	if (_timer != NULL)
	{
		SAFE_DELETE(_timer);
		_timer = NULL;
	}
}

void timeManager::update(float lock)
{
	//타이머 클래스가 있으면 업데이트한다
	if (_timer != NULL)
	{
		GetLocalTime(&time);
		_timer->tick(lock);
	}
}

void timeManager::render(ID2D1RenderTarget* RenderTarget)
{
	wchar_t str[256];
	string strFrame;
	DWInit(L"나눔고딕", 15, &WriteFactory, &TextFormat);
	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::White));


	TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
#ifdef _DEBUG
	if (_timer != nullptr)

		swprintf_s(str, TEXT("FPS: %ld"), _timer->getFPS());
		D2TextOut(RenderTarget, str, TextFormat, D2D1::RectF(0, 0, WINSIZEX_NUM, 0), Brush);
	}
#else
	if (_timer != nullptr)
	{
		swprintf_s(str, TEXT("FPS: %ld"), _timer->getFPS());
		D2TextOut(RenderTarget, str, TextFormat, D2D1::RectF(0, 0, WINSIZEX_NUM, 0), Brush);
	}
#endif
//	Brush->SetColor(D2D1::ColorF(D2D1::ColorF::Magenta));
//}