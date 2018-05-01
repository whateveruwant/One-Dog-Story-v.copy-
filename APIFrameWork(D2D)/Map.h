#pragma once
#include "gameNode.h"
#include "UIManager.h"
#include "dog.h"
#include "Door.h"
#include "bullet.h"
#include "Elevator.h"
#include "Object.h"
#include "invenItem.h"
#include "DropItem.h"
#include "Enemy.h"

class Map : public gameNode
{
private:
	tstring mapName;
	UIManager* UI;
	dog* mDog;
	bullet* bulletCollision;

	vector<Enemy*> vEnemy;
	vector<Door*> vDoor;
	vector<Object*> vObject;
	vector<Elevator*> vElevator;
	vector<DropItem*> vDropsItem;

	float time;
	float drainDump;

public:
	Map();
	~Map();

	HRESULT init(tstring name);
	void release(void);
	void update(void);
	void render(void);
	void updateEnemy(tstring _mapName);
	void updateDoor();
	void updateObject();
	void updateElevator();
	void changeMap(tstring _mapName);
	inline tstring getCurrentMap() { return mapName; }

	void loadDoor(tstring Mapname);
	void loadEnemy(tstring Mapname);
	void loadObject(tstring Mapname);
	void loadElevator(tstring Mapname);

	void loadSaveData(sSaveData& data);
	void deadSoGoBack();
	void levelCorrect(int level) {
		mDog->levelCorrect(level);
	}
};