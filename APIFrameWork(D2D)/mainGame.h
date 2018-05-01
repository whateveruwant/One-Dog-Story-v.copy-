#pragma once
#include "gameNode.h"
#include "loadingScene.h"
#include "menuScene.h"
#include "helpScene.h"
#include "mainGameScene.h"
#include "mainGameAgainScene.h"
#include "selectDataScene.h"
#include "selectNewDataScene.h"
#include "levelScene.h"
#include "soundScene.h"

class mainGame : public gameNode
{
public:
	mainGame();
	~mainGame();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};