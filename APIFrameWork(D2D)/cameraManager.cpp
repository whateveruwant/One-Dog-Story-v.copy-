#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	vibeTime = 0.0f;
	bossMode = false;
	speed = 6.0f;
	alpha = 1.0f;
	Rt->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, alpha), &black);
	black->SetColor(D2D1::ColorF(D2D1::ColorF::Black, alpha));
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
	if (alpha >= 0.0f) {
		alpha -= 0.01f;
	}

	black->SetColor(D2D1::ColorF(D2D1::ColorF::Black, alpha));
	drawCamera();
	_current.y = _standard->y;
	if (textMode) {
		if (TIMEMANAGER->getWorldTime() >= textTime) {
			textMode = false;
		}
	}
	if (TIMEMANAGER->getWorldTime() <= vibeTime) {
		_current.x -= (RND->getFromfloatTo(10.0f,0.0f) - 5);
	}
}

void cameraManager::render()
{
	if (textMode) {
		D2TextOut(Rt, TextStr, TextFormat, RectFMakeCenter(WINSIZEX_NUM/2, WINSIZEY_NUM - 100,500, 40), AquablueBrush);
	}

	Rt->FillRectangle(D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM), black);
}

D2D_POINT_2F cameraManager::getAbsPosition(const D2D_POINT_2F _pt)
{
	D2D_POINT_2F tmp;
	if (!bossMode) {
		tmp.x = _pt.x - _current.x + WINSIZEX_NUM / 2;
		tmp.y = _pt.y - _current.y + 50 + WINSIZEY_NUM / 2; // 50 + WINSIZEY_NUM / 2
	}
	else {
		tmp.x = _pt.x - _current.x + WINSIZEX_NUM / 2;
		tmp.y = _pt.y - _current.y + 200 + WINSIZEY_NUM / 2; // 50 + WINSIZEY_NUM / 2
	}
	return tmp;
}

void cameraManager::drawCamera()
{
	switch (*_direction)
	{
		float angle;
	case EViEWDIRECTION_LEFT:
		if (abs(getDistance(_current.x, _current.y, _standard->x - 100, _standard->y)) <= 5) {
			_current.x = _standard->x - 100;
			//_current.y = _standard->y;
		}
		else {
			angle = getAngle(_current.x, _current.y, _standard->x - 100, _standard->y);
			_current.x += cosf(angle * PI / 180) * speed;
			//_current.y -= sinf(angle * PI / 180) * speed;
		}
		break;
	case EViEWDIRECTION_RIGHT:
		if (int tmp = abs(getDistance(_current.x, _current.y, _standard->x + 100, _standard->y)) <= 5) {
			_current.x = _standard->x + 100;
			//_current.y = _standard->y;
		}
		else {
			angle = getAngle(_current.x, _current.y, _standard->x + 100, _standard->y);
			_current.x += cosf(angle * PI / 180) * speed;
			//_current.y -= sinf(angle * PI / 180) * speed;
		}
		break;
	case EViEWDIRECTION_UP:
		if (abs(getDistance(_current.x, _current.y, _standard->x, _standard->y)) <= 5) {
			_current.x = _standard->x;
			//_current.y = _standard->y;
		}
		else {
			angle = getAngle(_current.x, _current.y, _standard->x, _standard->y);
			_current.x += cosf(angle * PI / 180) *  speed;
			//_current.y -= sinf(angle * PI / 180) *  speed;
		}
		break;
	case EViEWDIRECTION_DOWN:
		if (abs(getDistance(_current.x, _current.y, _standard->x, _standard->y)) <= 5) {
			_current.x = _standard->x;
			//_current.y = _standard->y;
		}
		else {
			angle = getAngle(_current.x, _current.y, _standard->x, _standard->y);
			_current.x += cosf(angle * PI / 180) * speed;
			//_current.y -= sinf(angle * PI / 180) * speed;
		}
		break;
	}
}

void cameraManager::textOut(tstring str)
{
	tchar* tmpStr = (wchar_t *)str.c_str();
	wsprintf(TextStr, tmpStr);
	textMode = true;
	textTime = TIMEMANAGER->getWorldTime() + 2.0f;
}

void cameraManager::setVibeMode()
{
	vibeTime = TIMEMANAGER->getWorldTime() + 0.5f;
}
