#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	int _x, _y;			//��ǥ
	int _width;			//ü�¹� ���α���(�̰ɷ� ������)

	image* _progressBar;	//ü�¹� �� �̹���

public:
	progressBar();
	~progressBar();

	//ü�¹� �ʱ�ȭ(���̹���, ���̹���, x, y, ���α���, ���α���)
	HRESULT init(tchar* barImage, float x, float y, float width, float height);
	void release();
	void update();
	void render();

	//���α׷����� ������ ����
	void setGauge(float currentGauge, float maxGauge);

	//���α׷����� ��ġ
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};