#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager()
{
}

effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	viTotalEffect vIter;	//모든 이펙트 관리할 벡터
	miEffect mIter;			//이펙트 클래스 담겨 있는 맵

							//모든 이펙트를 관리할 벡터
	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//이펙트가 담겨있는 맵
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//이펙트 클래스 담은 벡터
				viEffect vArrIter;
				for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end();)
				{
					//이펙트 클래스 릴리즈
					(*vArrIter)->release();
					SAFE_DELETE(*vArrIter);
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void effectManager::update()
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render()
{
	viTotalEffect vIter;
	miEffect mIter;
	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(tstring effectKey, tchar * imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{
	image* img;
	vEffect vEffectBuffer;	//이펙트 버퍼
	mEffect mArrEffect;		//맵으로 만든 이펙트

							//이미지가 이미지 매니져에 등록이 되어 있으면
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		//이미지 새로 등록
		img = IMAGEMANAGER->addImage(Rt, effectKey, imageName, 0, 0, imageW, imageH, true);
	}

	//버퍼 크기만큼 이펙트를 동적할당 한 후 초기화해서 벡터를 만든다.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//벡터 담긴 이펙트 버퍼를 맵에 담는다.
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));

	//맵에 담긴 벡터를 토탈벡터에 담는다.
	m_vTotalEffect.push_back(mArrEffect);
}

void effectManager::play(tstring effectKey, float x, float y)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트 키값과 비교해서 같지 않으면 다음맵으로 넘김
			if (!(mIter->first == effectKey)) break;

			//이펙트키값과 일치하면 이펙트를 플레이
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}