#include "stdafx.h"
#include "image.h"

image::image() : _imageInfo(NULL), _fileName(NULL), _alpha(1.0f)
{
}


image::~image()
{
}

//이미지 파일로 초기화
HRESULT image::init(ID2D1RenderTarget* RenderTarget, const TCHAR* fileName, float x, float y, int width, int height, bool isCenter)
{
	HRESULT hr = S_OK;
	hr = D2DLoadBitmap(fileName, RenderTarget, imagingFactory, &_bitmap);
	if (FAILED(hr)) {
		return hr;
	}

	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) release();
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = wcslen(fileName);
	_fileName = new TCHAR[len + 1];
	wcsncpy_s(_fileName, len + 1, fileName, len + 1);

	_isCenter = isCenter;
	return S_OK;
}

//프레임 이미지 파일로 초기화
HRESULT image::init(ID2D1RenderTarget* RenderTarget, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isCenter)
{
	HRESULT hr = S_OK;
	hr = D2DLoadBitmap(fileName, RenderTarget, imagingFactory, &_bitmap);
	if (FAILED(hr)) {
		return hr;
	}

	//재초기화 방지용, 이미지 정보에 값이 들어 있다면 릴리즈먼저 해줄것!
	if (_imageInfo != NULL) release();
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	int len = wcslen(fileName);
	_fileName = new TCHAR[len + 1];
	wcsncpy_s(_fileName, len + 1, fileName, len + 1);

	_isCenter = isCenter;
	return S_OK;
}

//==================================================================
//		## 일반렌더 ##
//==================================================================
void image::render(ID2D1RenderTarget* RenderTarget)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			_imageInfo->x - _imageInfo->width / 2,
			_imageInfo->y - _imageInfo->height / 2,
			_imageInfo->x + _imageInfo->width / 2,
			_imageInfo->y + _imageInfo->height / 2), _alpha);
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(_imageInfo->x, _imageInfo->y,
				_imageInfo->x + _imageInfo->width,
				_imageInfo->y + _imageInfo->height), _alpha);
	}
}

void image::render(ID2D1RenderTarget* RenderTarget, float x, float y)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			x - _imageInfo->width / 2,
			y - _imageInfo->height / 2,
			x + _imageInfo->width / 2,
			y + _imageInfo->height / 2), _alpha);
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(x, y,
				x + _imageInfo->width,
				y + _imageInfo->height), _alpha);
	}
}

void image::render(ID2D1RenderTarget * RenderTarget, float x, float y, float sourceWidth, float sourceHeight)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			x - sourceWidth / 2,
			y - sourceHeight / 2,
			x + sourceWidth / 2,
			y + sourceHeight / 2), _alpha);
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(x, y,
				x + sourceWidth,
				y + sourceHeight), _alpha);
	}
}

void image::render(ID2D1RenderTarget * RenderTarget, float x, float y, float sourceX, float sourceY, float sourceWidth, float sourceHeight)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			x - _imageInfo->width / 2,
			y + _imageInfo->height / 2 - sourceHeight,
			x + _imageInfo->width / 2,
			y + _imageInfo->height / 2), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(
				_imageInfo->x - sourceWidth / 2,
				_imageInfo->y + _imageInfo->height / 2 - sourceHeight /2,
				_imageInfo->x + sourceWidth / 2,
				_imageInfo->y + _imageInfo->height / 2));
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(x, y,
				x + _imageInfo->width,
				y + _imageInfo->height), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(sourceX, sourceY,
					sourceX + sourceWidth,
					sourceY + sourceHeight));
	}
}

//==================================================================
//		## 알파렌더 ##
//==================================================================
void image::alphaRender(ID2D1RenderTarget* RenderTarget, float alpha)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			_imageInfo->x - _imageInfo->width / 2,
			_imageInfo->y - _imageInfo->height / 2,
			_imageInfo->x + _imageInfo->width / 2,
			_imageInfo->y + _imageInfo->height / 2), alpha);
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(_imageInfo->x, _imageInfo->y,
				_imageInfo->x + _imageInfo->width,
				_imageInfo->y + _imageInfo->height), alpha);
	}
}

void image::alphaRender(ID2D1RenderTarget * RenderTarget, float x, float y, float alpha)
{
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
			x - _imageInfo->width / 2,
			y - _imageInfo->height / 2,
			x + _imageInfo->width / 2,
			y + _imageInfo->height / 2), alpha);
	}
	else {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(x, y,
				x + _imageInfo->width,
				y + _imageInfo->height), alpha);
	}
}

//==================================================================
//		## 프레임렌더 ##
//==================================================================
void image::frameRender(ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}
	
	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(_imageInfo->x - _imageInfo->frameWidth / 2,
				_imageInfo->y - _imageInfo->frameHeight / 2,
				_imageInfo->x + _imageInfo->frameWidth / 2,
				_imageInfo->y + _imageInfo->frameHeight / 2),
			_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
	else {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(_imageInfo->x, _imageInfo->y,
			_imageInfo->x + _imageInfo->frameWidth,
			_imageInfo->y + _imageInfo->frameHeight), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
}

void image::frameRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(x - _imageInfo->frameWidth / 2,
				y - _imageInfo->frameHeight / 2,
				x + _imageInfo->frameWidth / 2,
				y + _imageInfo->frameHeight / 2),
			_alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
	else {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(x, y,
			x + _imageInfo->frameWidth,
			y + _imageInfo->frameHeight), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
}

//==================================================================
//		## 알파프레임렌더 ##
//==================================================================
void image::frameAlphaRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isCenter) {
		RenderTarget->DrawBitmap(_bitmap,
			D2D1::RectF(_imageInfo->x - _imageInfo->frameWidth / 2,
				_imageInfo->y - _imageInfo->frameHeight / 2,
				_imageInfo->x + _imageInfo->frameWidth / 2,
				_imageInfo->y + _imageInfo->frameHeight / 2),
			alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
	else {
		RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(_imageInfo->x, _imageInfo->y,
			_imageInfo->x + _imageInfo->frameWidth,
			_imageInfo->y + _imageInfo->frameHeight), alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
				(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
				(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
	}
}

void image::bottomRender(ID2D1RenderTarget * RenderTarget)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		_imageInfo->x - _imageInfo->frameWidth / 2,
		_imageInfo->y - _imageInfo->frameHeight,
		_imageInfo->x + _imageInfo->frameWidth / 2,
		_imageInfo->y), _alpha);
}

void image::bottomRender(ID2D1RenderTarget * RenderTarget, float x, float y)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		x - _imageInfo->width / 2,
		y - _imageInfo->height,
		x + _imageInfo->width / 2,
		y), _alpha);
}

void image::bottomFillOpacityRender(ID2D1RenderTarget * RenderTarget, float x, float y, ID2D1Brush * Brush)
{
	RenderTarget->FillOpacityMask(_bitmap, Brush, D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL, D2D1::RectF(
		x - _imageInfo->width / 2,
		y - _imageInfo->height,
		x + _imageInfo->width / 2,
		y), D2D1::RectF(
		x - _imageInfo->width / 2,
		y - _imageInfo->height,
		x + _imageInfo->width / 2,
		y));
}

void image::bottomAlphaRender(ID2D1RenderTarget * RenderTarget, float alpha)
{
	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		_imageInfo->x - _imageInfo->frameWidth / 2,
		_imageInfo->y - _imageInfo->frameHeight,
		_imageInfo->x + _imageInfo->frameWidth / 2,
		_imageInfo->y),	alpha);
}

void image::bottomFrameRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		_imageInfo->x - _imageInfo->frameWidth / 2,
		_imageInfo->y - _imageInfo->frameHeight,
		_imageInfo->x + _imageInfo->frameWidth / 2,
		_imageInfo->y)	, _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
		(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}

void image::bottomFrameRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		x - _imageInfo->frameWidth / 2,
		y - _imageInfo->frameHeight,
		x + _imageInfo->frameWidth / 2,
		y), _alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
			(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}

void image::bottomFrameFillOpacityRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float x, float y, ID2D1Brush * Brush)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	RenderTarget->FillOpacityMask(_bitmap, Brush, D2D1_OPACITY_MASK_CONTENT_TEXT_NATURAL, D2D1::RectF(
		x - _imageInfo->frameWidth / 2,
		y - _imageInfo->frameHeight,
		x + _imageInfo->frameWidth / 2,
		y), D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
			(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
			(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));

}

void image::bottomFrameAlphaRender(ID2D1RenderTarget * RenderTarget, int currentFrameX, int currentFrameY, float alpha)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	RenderTarget->DrawBitmap(_bitmap, D2D1::RectF(
		_imageInfo->x - _imageInfo->frameWidth / 2, 
		_imageInfo->y - _imageInfo->frameHeight,
		_imageInfo->x + _imageInfo->frameWidth / 2,
		_imageInfo->y), alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		D2D1::RectF((_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*_imageInfo->currentFrameX,
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*_imageInfo->currentFrameY,
		(_bitmap->GetSize().width / (_imageInfo->maxFrameX + 1))*(_imageInfo->currentFrameX + 1),
		(_bitmap->GetSize().height / (_imageInfo->maxFrameY + 1))*(_imageInfo->currentFrameY + 1)));
}

void image::aniRender(ID2D1RenderTarget * RenderTarget, float destX, float destY, animation* ani)
{
	frameRender(Rt, ani->getFrameCount().x, ani->getFrameCount().y, destX, destY);
}

void image::aniBottomRender(ID2D1RenderTarget * RenderTarget, float destX, float destY, animation * ani)
{
	bottomFrameRender(Rt, ani->getFrameCount().x, ani->getFrameCount().y, destX, destY);
}

void image::aniBottomFillOpacityRender(ID2D1RenderTarget * RenderTarget, float destX, float destY, animation * ani, ID2D1Brush * Brush)
{
	bottomFrameFillOpacityRender(Rt, ani->getFrameCount().x, ani->getFrameCount().y, destX, destY, Brush);
}

void image::release()
{
	if (_imageInfo)
	{
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		//SAFE_RELEASE(_bitmap);
	}
}