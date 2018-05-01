#pragma once
#include "singletonBase.h"

//���ӳ�� Ŭ���� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene;	//�����
	mSceneList _mSceneList;			//�� ���

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�� �߰�
	gameNode* addScene(string sceneName, gameNode* scene);
	//�� ����
	HRESULT changeScene(string sceneName);

	sceneManager();
	~sceneManager();
};

