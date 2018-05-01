#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

sceneManager::sceneManager()
{
}

sceneManager::~sceneManager()
{
}

//����ƽ���� ������� �ΰ����� �ʱ�ȭ
gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init(void)
{
	return S_OK;
}

void sceneManager::release(void)
{
	//�ݺ��ڸ� ���ؼ� ���� ���鼭 �ϳ��� �����Ѵ�.
	miSceneList iter = _mSceneList.begin();
	for (iter; iter != _mSceneList.end();)
	{
		//����
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			//iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//�� �߰�
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

//�� ����
HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//��ã������ E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//������� ������ ������ ������ ���� �ʱ�ȭ�ϰ� �������ش�
	if (SUCCEEDED(find->second->init()))
	{
		//Ȥ�� �������� ������ ������
		//if (_currentScene) _currentScene->release();
	//	if(_currentScene)
//			_currentScene->release();
		_currentScene = find->second;


		return S_OK;
	}
	return E_FAIL;
}