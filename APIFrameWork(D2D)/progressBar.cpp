#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(tchar* barImage, float x, float y, float width, float height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;

	//체력바 이미지 초기화
	_progressBar = new image;
	_progressBar->init(Rt, barImage, x, y, width, height, false);

	//가로 길이 초기화
	_width = _progressBar->getWidth();

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBar);
}

void progressBar::update()
{
}

void progressBar::render()
{
	_progressBar->render(Rt, _x, _y, _width, 18);
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBar->getWidth();
}
