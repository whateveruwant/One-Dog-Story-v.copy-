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
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBar = new image;
	_progressBar->init(Rt, barImage, x, y, width, height, false);

	//���� ���� �ʱ�ȭ
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
