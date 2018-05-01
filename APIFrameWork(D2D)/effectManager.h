#pragma once
#include "singletonBase.h"
//#include "effect.h"

class effect;

class effectManager : public singletonBase<effectManager>
{
private:
	//이펙트 클래스 담은 벡터
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//이펙트 클래스가 담겨있는 벡터를 담은 맵
	typedef map<tstring, vEffect> mEffect;
	typedef map<tstring, vEffect>::iterator miEffect;
	//모든 이펙트를 관리할 벡터(이펙트가 담겨 있는 벡터를 담은 맵을 다시 담은 벡터)
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

	//실제 모든 이펙트가 담겨 있는 벡터
	vTotalEffect m_vTotalEffect;

public:
	effectManager();
	~effectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//이펙트 추가(키값, 이미지 이름, 이미지 가로크기, 세로크기, 한프레임 가로크기, 세로크기, FPS ,이펙트 속도, 버퍼갯수)
	void addEffect(tstring effectKey, tchar* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	//이펙트 플레이(이펙트 키값, 이펙트 터트릴 좌표)
	void play(tstring effectKey, float x, float y);
};