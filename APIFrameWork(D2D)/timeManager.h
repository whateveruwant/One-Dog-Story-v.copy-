#pragma once
#include "singletonBase.h"
#include "timer.h"
//==================================================================
//		## timeManager ## (Ÿ�ӸŴ���)
//==================================================================

class timeManager : public singletonBase <timeManager>
{
private:
	timer* _timer;	//Ÿ�̸� Ŭ����
	SYSTEMTIME time;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(ID2D1RenderTarget* RenderTarget);

	//�������Ӵ� ����ð�(1 / 60) ��������
	float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	//��ü ����ð� ��������
	float getWorldTime(void) const { return _timer->getWorldTime(); }
	unsigned long getFPS() { return _timer->getFrameRate(); }

	tchar* getCurrentInfo() {
		tchar info[100];
		wsprintf(info, L"%d/%d/%d %d�� %d�� %d��", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
		return info;
	}
	timeManager();
	~timeManager();
};