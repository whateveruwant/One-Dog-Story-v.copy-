#include "stdafx.h"
#include "animationManager.h"

animationManager::animationManager()
{
}

animationManager::~animationManager()
{
}

HRESULT animationManager::init()
{
	return S_OK;
}

void animationManager::release()
{
	deleteALL();
}

void animationManager::update()
{
	iterArrAnimation iter = m_animation.begin();
	for (iter; iter != m_animation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}
}

void animationManager::render()
{
}

void animationManager::addDefAnimation(tstring animationKeyName, tchar * imageKeyName, int fps, bool reverse, bool loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(tstring animationKeyName, tchar * imageKeyName, int * playArr, int arrLen, int fps, bool loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(playArr, arrLen, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::addAnimation(tstring animationKeyName, tchar * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다.
	m_animation.insert(make_pair(animationKeyName, ani));
}

void animationManager::start(tstring animationKeyName)
{
	iterArrAnimation iter = m_animation.find(animationKeyName);
	iter->second->start();
}

void animationManager::stop(tstring animationKeyName)
{
	iterArrAnimation iter = m_animation.find(animationKeyName);
	iter->second->stop();
}

void animationManager::pause(tstring animationKeyName)
{
	iterArrAnimation iter = m_animation.find(animationKeyName);
	iter->second->pause();
}

void animationManager::resume(tstring animationKeyName)
{
	iterArrAnimation iter = m_animation.find(animationKeyName);
	iter->second->resume();
}

animation * animationManager::findAnimation(tstring animationKeyName)
{
	iterArrAnimation iter = m_animation.find(animationKeyName);
	if (iter != m_animation.end())
	{
		return iter->second;
	}

	return nullptr;
}

void animationManager::deleteALL()
{
	iterArrAnimation iter = m_animation.begin();
	for (; iter != m_animation.end();)
	{
		if (iter->second != NULL)
		{
			//애니메이션 클래스 삭제
			SAFE_DELETE(iter->second);
			//반복자 삭제
			iter = m_animation.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}