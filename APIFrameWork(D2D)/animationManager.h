#pragma once
#include "singletonBase.h"
#include "image.h"

class animationManager : public singletonBase<animationManager>
{
private:
	typedef map<tstring, animation*> arrAnimation;
	typedef map<tstring, animation*>::iterator iterArrAnimation;

	arrAnimation m_animation;
public:
	animationManager();
	~animationManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//처음부터 끝까지
	void addDefAnimation(tstring animationKeyName, tchar* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//배열에 담아서
	void addAnimation(tstring animationKeyName, tchar* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//구간 정해서
	void addAnimation(tstring animationKeyName, tchar* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	//플레이
	void start(tstring animationKeyName);
	//정지
	void stop(tstring animationKeyName);
	//일시정지
	void pause(tstring animationKeyName);
	//다시 재생
	void resume(tstring animationKeyName);

	//애니메이션 찾기
	animation* findAnimation(tstring animationKeyName);

	//애니메이션 찾기 삭제
	void deleteALL();
};