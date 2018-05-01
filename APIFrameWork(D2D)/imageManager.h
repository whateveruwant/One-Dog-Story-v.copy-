#pragma once
#include "SingletonBase.h"
#include "image.h"

//==================================================================
//		## imageManager ## (�̹��� �Ŵ���)
//==================================================================
class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<tstring, image*> mapImageList;
	typedef map<tstring, image*>::iterator mapImageIter;

private:
	mapImageList m_imageList;	// ������ ������ �̹��� ���

public:
	imageManager();
	~imageManager();

	// �̹��� �Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	// �̹��� �Ŵ��� ����
	void release(void);

	// Ű������ �̹��� ���� �ʱ�ȭ
	image* addImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, float x, float y, int width, int height, bool isCenter);
	// Ű������ ������ �̹��� ���� �ʱ�ȭ
	image* addFrameImage(ID2D1RenderTarget* RenderTarget, tstring strKey, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isCenter);


	// �̹��� Ű���� ã��
	image* findImage(tstring strKey);
	bool searchImage(tstring strKey);
	// �̹��� Ű������ ����
	bool deleteImage(tstring strKey);
	// �̹��� ��ü ����
	bool deleteAll(void);

	//==================================================================
	//		## �Ϲݷ��� ##
	//==================================================================
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y, float sourceWidth, float sourceHeight);
	void render(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y, float sourceX, float sourceY, float sourceWidth, float sourceHeight);
	void bottomFillOpacityRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y, ID2D1Brush* Brush);

	//==================================================================
	//		## ���ķ��� ##
	//==================================================================
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float alpha);
	void alphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y, float alpha);

	//==================================================================
	//		## �����ӷ��� ##
	//==================================================================
	void frameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY);
	void frameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY, float x, float y);

	//==================================================================
	//		## ���������ӷ��� ##
	//==================================================================
	void frameAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY, float alpha);

	//==================================================================
	//		## bottom�Ϲݷ��� ##
	//==================================================================
	void bottomRender(tstring strKey, ID2D1RenderTarget* RenderTarget);
	void bottomRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float x, float y);

	//==================================================================
	//		## bottom���ķ��� ##
	//==================================================================
	void bottomAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, float alpha);

	//==================================================================
	//		## bottom�����ӷ��� ##
	//==================================================================
	void  bottomFrameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY);
	void  bottomFrameRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY, float x, float y);
	void  bottomFrameFillOpacityRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY, float x, float y, ID2D1Brush* Brush);

	//==================================================================
	//		## bottom���������ӷ��� ##
	//==================================================================
	void  bottomFrameAlphaRender(tstring strKey, ID2D1RenderTarget* RenderTarget, int currentFrameX, int currentFrameY, float alpha);
};