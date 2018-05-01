#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	loading* _loading;

public:
	loadingScene();
	~loadingScene();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void totalLoading();
};