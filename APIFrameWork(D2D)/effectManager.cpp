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
	viTotalEffect vIter;	//��� ����Ʈ ������ ����
	miEffect mIter;			//����Ʈ Ŭ���� ��� �ִ� ��

							//��� ����Ʈ�� ������ ����
	for (vIter = m_vTotalEffect.begin(); vIter != m_vTotalEffect.end(); ++vIter)
	{
		//����Ʈ�� ����ִ� ��
		for (mIter = vIter->begin(); mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				//����Ʈ Ŭ���� ���� ����
				viEffect vArrIter;
				for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end();)
				{
					//����Ʈ Ŭ���� ������
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
	vEffect vEffectBuffer;	//����Ʈ ����
	mEffect mArrEffect;		//������ ���� ����Ʈ

							//�̹����� �̹��� �Ŵ����� ����� �Ǿ� ������
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		//�̹��� ���� ���
		img = IMAGEMANAGER->addImage(Rt, effectKey, imageName, 0, 0, imageW, imageH, true);
	}

	//���� ũ�⸸ŭ ����Ʈ�� �����Ҵ� �� �� �ʱ�ȭ�ؼ� ���͸� �����.
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//���� ��� ����Ʈ ���۸� �ʿ� ��´�.
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));

	//�ʿ� ��� ���͸� ��Ż���Ϳ� ��´�.
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
			//����Ʈ Ű���� ���ؼ� ���� ������ ���������� �ѱ�
			if (!(mIter->first == effectKey)) break;

			//����ƮŰ���� ��ġ�ϸ� ����Ʈ�� �÷���
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