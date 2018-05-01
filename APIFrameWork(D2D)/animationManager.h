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

	//ó������ ������
	void addDefAnimation(tstring animationKeyName, tchar* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//�迭�� ��Ƽ�
	void addAnimation(tstring animationKeyName, tchar* imageKeyName, int* playArr, int arrLen, int fps, bool loop = false);
	//���� ���ؼ�
	void addAnimation(tstring animationKeyName, tchar* imageKeyName, int start, int end, int fps, bool reverse = false, bool loop = false);

	//�÷���
	void start(tstring animationKeyName);
	//����
	void stop(tstring animationKeyName);
	//�Ͻ�����
	void pause(tstring animationKeyName);
	//�ٽ� ���
	void resume(tstring animationKeyName);

	//�ִϸ��̼� ã��
	animation* findAnimation(tstring animationKeyName);

	//�ִϸ��̼� ã�� ����
	void deleteALL();
};