#include "stdafx.h"
#include "mainGame.h"

mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

HRESULT mainGame::init(void)
{
	gameNode::init(true);
	SCENEMANAGER->addScene("loadingSC", new loadingScene);
	SCENEMANAGER->addScene("mainGameSC", new mainGameScene);
	SCENEMANAGER->addScene("mainGameAgainSC", new mainGameAgainScene);
	SCENEMANAGER->addScene("menuSC", new menuScene);
	SCENEMANAGER->addScene("helpSC", new helpScene);
	SCENEMANAGER->addScene("selectDataSC", new selectDataScene);
	SCENEMANAGER->addScene("selectNewDataSC", new selectNewDataScene);
	SCENEMANAGER->addScene("levelSC", new levelScene);
	SCENEMANAGER->addScene("soundSC", new soundScene);

	SCENEMANAGER->changeScene("loadingSC");
	return S_OK;
}

void mainGame::release(void)
{
	gameNode::release();
}

void mainGame::update(void)
{
	gameNode::update();
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
	ANIMATIONMANAGER->update();
	EFFECTMANAGER->update();
}

void mainGame::render(void)
{
	gameNode::render();
	Rt->BeginDraw();
	Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	Rt->Clear();

	D2D1_RECT_F rect = D2D1::RectF(0, 0, WINSIZEX_NUM, WINSIZEY_NUM);
	//==================================================================
	SCENEMANAGER->render();
	//==================================================================
	TIMEMANAGER->render(Rt);
	Rt->EndDraw();
}