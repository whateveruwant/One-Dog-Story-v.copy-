#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

HRESULT Map::init(tstring name)
{

	drainDump = 0;
	time = 0;

	mapName = name;
	mDog = new dog;
	mDog->init(mapName);

	UI = new UIManager;
	UI->init();
	UI->setMemoryHP(*mDog->getAddreesMaxHp(), *mDog->getAddreescurrentHp());
	UI->setMemoryDogInven(*mDog->getInvenMemory());
	UI->setMemoryDogWeapon(*mDog->getWeaponMemory());
	UI->setMemoryMoney(*mDog->getAddreesMoney());

	bulletCollision = new bullet;
	bulletCollision->init();
	bulletCollision->setClubRect(mDog->getClubRectMemory());
	bulletCollision->setDogWeaponMemory(mDog->getWeaponMemory());
	bulletCollision->setDogMemory(mDog);

	loadEnemy(name);
	loadDoor(name);
	loadObject(name);
	loadElevator(name);

	return S_OK;
}

void Map::release(void)
{
	UI->release();
	SAFE_DELETE(UI);
	mDog->release();
	SAFE_DELETE(mDog);
	bulletCollision->release();
	SAFE_DELETE(bulletCollision);
}

void Map::update(void)
{
	UI->update();
	if (!mDog->getisDead()) {
		updateElevator();
		mDog->update(mapName);
		updateEnemy(mapName);
		updateDoor();
		updateObject();
		bulletCollision->update();
		for (int i = 0; i < vDropsItem.size(); ++i) {
			vDropsItem.at(i)->update();
			if (IsInRect(vDropsItem.at(i)->getPoint(), *mDog->getRectMemory())) {
				switch (vDropsItem.at(i)->getKind())
				{
				case EDROPITEM_NONE:
					break;
				case EDROPITEM_HEAL:
					SOUNDMANAGER->play("coin", 1.0f * effectSound);
					mDog->plusHealth();
					break;
				case EDROPITEM_MONEY:
					SOUNDMANAGER->play("coin", 1.0f * effectSound);
					mDog->plusMoney();
					break;
				case EDROPITEM_BULLET:
					SOUNDMANAGER->play("coin", 1.0f * effectSound);
					mDog->plusBullet();
					break;
				}
				vector<DropItem*>::iterator vIter = vDropsItem.begin();
				vIter += i;
				vDropsItem.erase(vIter);
			}
		}
	}
	else {
		if (time == 0) time = TIMEMANAGER->getWorldTime() + 3.0f;
		else if (TIMEMANAGER->getWorldTime() >= time) {
			deadSoGoBack();
		}
	}
}

void Map::render(void)
{
	IMAGEMANAGER->render(mapName, Rt, CAMERAMANAGER->getAbsPosition({ 0, 0 }).x, CAMERAMANAGER->getAbsPosition({ 0,0 }).y);
	for (int i = 0; i < vDoor.size(); ++i) {
		vDoor.at(i)->render();
	}
	for (int i = 0; i < vObject.size(); ++i) {
		if (vObject.at(i)->getImageName() == L"depot") {
			((Object_TOOL*)vObject.at(i))->render();
		}
		else {
			(vObject.at(i))->render();
		}
	}
	for (int i = 0; i < vElevator.size(); ++i) {
		vElevator.at(i)->render();
	}
	for (int i = 0; i < vDropsItem.size(); ++i) {
		vDropsItem.at(i)->render();
	}

	int tmpboss = -1;
	for (int i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy.at(i)->getName() == L"1st_boss") {
			tmpboss = i;
			continue;
		}
		else {
			vEnemy.at(i)->render();
		}
	}
	if (tmpboss != -1) {
		((Enemy_BOSS*)vEnemy.at(tmpboss))->render();
	}
	bulletCollision->render();
	mDog->render();
	EFFECTMANAGER->render();
	Rt->FillRectangle({ 0,0,WINSIZEX_NUM,WINSIZEY_NUM }, m_pRadialGradientBrush);
	UI->render();
	if (mDog->getisDead()) {
		IMAGEMANAGER->render(L"redHeart", Rt);
	}
}

void Map::updateEnemy(tstring _mapName)
{
	for (int i = 0; i < vEnemy.size(); ++i) {
		if (vEnemy.at(i)->getName() == L"1st_boss") {
			((Enemy_BOSS*)vEnemy.at(i))->update(_mapName);
			vector<EBOSSBULLET>* vBulletTmp = ((Enemy_BOSS*)vEnemy.at(i))->getBossBullet();
			for (int i = 0; i < vBulletTmp->size(); ++i) {
				if (CheckCollisionRects(*mDog->getRectMemory(), vBulletTmp->at(i).rect)) {
					mDog->damage(2);
					mDog->compulsionJump();
					vector<EBOSSBULLET>::iterator viBullet = vBulletTmp->begin();
					viBullet += i;
					vBulletTmp->erase(viBullet);
					break;
				}
			}
			if (*((Enemy_BOSS*)vEnemy.at(i))->getCreate()) {
				SOUNDMANAGER->play("slugDown", 1.0f * effectSound);
				SENEMY tmpInfo;
				image* tmpBG = IMAGEMANAGER->findImage(mapName);
				tmpInfo.kind = EENEMYKIND_MADE;
				switch (RND->getInt(2))
				{
				case 0:
					tmpInfo.x = (((Enemy_BOSS*)vEnemy.at(i))->getPosition().x + 100)/ tmpBG->getWidth();
					break;
				case 1:
					tmpInfo.x = (((Enemy_BOSS*)vEnemy.at(i))->getPosition().x - 100) / tmpBG->getWidth();
					break;
				}
				tmpInfo.y = (((Enemy_BOSS*)vEnemy.at(i))->getPosition().y + 100) / tmpBG->getHeight();
				wsprintf(tmpInfo.name, L"slime_green");
				Enemy* ptmpEnemy = new Enemy;
				ptmpEnemy->init(tmpInfo, mapName);
				ptmpEnemy->setDogPositionMemory(mDog->getPoint());
				vEnemy.push_back(ptmpEnemy);
				bulletCollision->addTheSomeThings(vEnemy.back()->getRectMemory(), vEnemy.back()->getIsAttackMemory(), vEnemy.back()->getIsDeleteMemory(), vEnemy.back()->getDamageMemory());
				bool* crt = ((Enemy_BOSS*)vEnemy.at(i))->getCreate();
				*crt = false;
				break;
			}
		}
		else {
			vEnemy.at(i)->update(_mapName);
			if (*vEnemy.at(i)->getIsDeleteMemory() == true && vEnemy.at(i)->getName() != L"egg") {
				for (int j = 0;j < 2; ++j) {
					DropItem* tmp;
					tmp = new DropItem;
					switch (RND->getInt(5))
					{
					case 0:
						tmp->init(EDROPITEM_HEAL, vEnemy.at(i)->getPosition().x - 10 + j * 10, vEnemy.at(i)->getPosition().y - 10 + j * 10);
						break;
					case 1:
						tmp->init(EDROPITEM_MONEY, vEnemy.at(i)->getPosition().x - 10 + j * 10, vEnemy.at(i)->getPosition().y - 10 + j * 10);
						break;
					case 2:
						tmp->init(EDROPITEM_BULLET, vEnemy.at(i)->getPosition().x - 10 + j * 10, vEnemy.at(i)->getPosition().y - 10 + j * 10);
						break;
					default:
						break;
					}
					tmp->setDogPosition(*mDog->getPoint());
					vDropsItem.push_back(tmp);
				}
				vector<Enemy*>::iterator viEnemy = vEnemy.begin();
				viEnemy += i;
				vEnemy.at(i)->release();
				vEnemy.erase(viEnemy);
				break;
			}
			if (CheckCollisionRects(*vEnemy.at(i)->getRectMemory(), *mDog->getRectMemory()) && !mDog->getisTrans() && *vEnemy.at(i)->getAction() != EENEMYACTKIND_DEATH) {
				mDog->damage(2);
				mDog->compulsionJump();
				break;
			}
			if (*vEnemy.at(i)->getCreate()) {
				SENEMY tmpInfo;
				image* tmpBG = IMAGEMANAGER->findImage(mapName);
				tmpInfo.kind = EENEMYKIND_MADE;
				tmpInfo.x = vEnemy.at(i)->getPosition().x / tmpBG->getWidth();
				tmpInfo.y = vEnemy.at(i)->getPosition().y / tmpBG->getHeight();
				wsprintf(tmpInfo.name, L"spider");
				Enemy* ptmpEnemy = new Enemy;
				ptmpEnemy->init(tmpInfo, mapName);
				ptmpEnemy->setDogPositionMemory(mDog->getPoint());
				vEnemy.push_back(ptmpEnemy);
				bulletCollision->deleteSomeThings(vEnemy.at(i)->getRectMemory(), vEnemy.at(i)->getIsAttackMemory(), vEnemy.at(i)->getIsDeleteMemory(), vEnemy.at(i)->getDamageMemory());
				bulletCollision->addTheSomeThings(vEnemy.back()->getRectMemory(), vEnemy.back()->getIsAttackMemory(), vEnemy.back()->getIsDeleteMemory(), vEnemy.back()->getDamageMemory());
				EENEMYACTKIND* action = vEnemy.at(i)->getAction();
				*action = EENEMYACTKIND_DEATH;
				bool* crt = vEnemy.at(i)->getCreate();
				*crt = false;
				break;
			}
		}
	}
}

void Map::updateDoor()
{
	for (int i = 0; i < vDoor.size(); ++i) {
		vDoor.at(i)->update();
		if (vDoor.at(i)->getGoChangeMap()) {
			changeMap(vDoor.at(i)->getChangeMapName());
			image tmpMap = *IMAGEMANAGER->findImage(mapName);
			mDog->update(mapName);
			mDog->movePosition({ vDoor.at(i)->getChangePosition().x * tmpMap.getWidth(),  vDoor.at(i)->getChangePosition().y * tmpMap.getHeight() });
			loadEnemy(mapName);
			loadDoor(mapName);
			loadElevator(mapName);
			loadObject(mapName);
			setRadialGradientBrush(Rt, {WINSIZEX_NUM/2 , WINSIZEY_NUM/2}, 1000, 1000, 1);
		}
		else if (vDoor.at(i)->getisOpening()) {
			setRadialGradientBrush(Rt, { CAMERAMANAGER->getAbsPosition(*mDog->getPoint()).x, CAMERAMANAGER->getAbsPosition(*mDog->getPoint()).y - 50 }, m_pRadialGradientBrush->GetRadiusX(), m_pRadialGradientBrush->GetRadiusY(), 1);
			m_pRadialGradientBrush->SetRadiusX(m_pRadialGradientBrush->GetRadiusX() - 13);
			m_pRadialGradientBrush->SetRadiusY(m_pRadialGradientBrush->GetRadiusY() - 13);
		}
	}
}

void Map::updateObject()
{
	for (int i = 0; i < vObject.size(); ++i) {
		if (vObject.at(i)->getImageName() == L"depot") {
			((Object_TOOL*)vObject.at(i))->update();
		}
		else if (vObject.at(i)->getImageName() == L"spike" || vObject.at(i)->getImageName() == L"spike_up" || vObject.at(i)->getImageName() == L"spike_left" || vObject.at(i)->getImageName() == L"spike_right") {
			((Object_DAMAGE*)vObject.at(i))->update();
			if (((Object_DAMAGE*)vObject.at(i))->getIsTouch() && !mDog->getisTrans()) {
				mDog->damage(2);
				mDog->compulsionJump();
			}
		}
		else if (vObject.at(i)->getImageName() == L"firePillar") {
			((Object_DAMAGE*)vObject.at(i))->update();
			if (((Object_DAMAGE*)vObject.at(i))->getIsTouch() && !mDog->getisTrans()) {
				mDog->damage(5);
				mDog->compulsionJump();
			}
		}
		else if (vObject.at(i)->getImageName() == L"press") {
			((Object_DAMAGE*)vObject.at(i))->update();
			if (((Object_DAMAGE*)vObject.at(i))->getIsTouch() && !mDog->getisTrans()) {
				mDog->damage(100);
			}
		}
		else if (vObject.at(i)->getImageName() == L"box") {
			((Object_BOX*)vObject.at(i))->update();
		}
		else if (vObject.at(i)->getImageName() == L"health" || vObject.at(i)->getImageName() == L"upgrade" || vObject.at(i)->getImageName() == L"bullet") {
			((Object_ITEM*)vObject.at(i))->update();
			if (((Object_ITEM*)vObject.at(i))->getIsUse()) {
				vector<Object*>::iterator viObject = vObject.begin();
				viObject += i;
				vObject.erase(viObject);
				break;
			}
		}
		else if (vObject.at(i)->getImageName() == L"healmachine" || vObject.at(i)->getImageName() == L"upgrademachine" || vObject.at(i)->getImageName() == L"savemachine") {
			((Object_VENDING*)vObject.at(i))->update();
		}
		else if (vObject.at(i)->getImageName() == L"drain") {
			if ((int)TIMEMANAGER->getWorldTime() % 5 == 0 && vObject.at(i)->getTime() != (int)TIMEMANAGER->getWorldTime() &&
				(vObject.at(i)->getPoint().x <= mDog->getPoint()->x + 1000 && vObject.at(i)->getPoint().x >= mDog->getPoint()->x - 1000) &&
				(vObject.at(i)->getPoint().y <= mDog->getPoint()->y + 1000 && vObject.at(i)->getPoint().y >= mDog->getPoint()->y - 1000)) {
				vObject.at(i)->setTime(TIMEMANAGER->getWorldTime());
				SENEMY tmpInfo;
				image* tmpBG = IMAGEMANAGER->findImage(mapName);
				tmpInfo.kind = EENEMYKIND_MADE;
				tmpInfo.x = vObject.at(i)->getPoint().x / tmpBG->getWidth();
				tmpInfo.y = vObject.at(i)->getPoint().y / tmpBG->getHeight();
				wsprintf(tmpInfo.name, L"slime_green");
				Enemy* ptmpEnemy = new Enemy;
				ptmpEnemy->init(tmpInfo, mapName);
				ptmpEnemy->setDogPositionMemory(mDog->getPoint());
				vEnemy.push_back(ptmpEnemy);
				bulletCollision->addTheSomeThings(vEnemy.back()->getRectMemory(), vEnemy.back()->getIsAttackMemory(), vEnemy.back()->getIsDeleteMemory(), vEnemy.back()->getDamageMemory());
			}
		}
		else {
			(vObject.at(i))->update();
		}
	}

	//에스컬레이터 실행
	for (int i = 0; i < vObject.size(); ++i) {
		if (vObject.at(i)->getImageName() == L"escalator") {
			if (vObject.at(i)->getIsTouch()) {
				mDog->modifyX(2.5f);
				break;
			}
		}
	}
}

void Map::updateElevator()
{
	for (int i = 0; i < vElevator.size(); ++i) {
		vElevator.at(i)->update();
		if (vElevator.at(i)->getKind() == EELEVATORKIND_LASER && vElevator.at(i)->getOnLift()) {
			mDog->damage(100);
		}
	}
}

void Map::changeMap(tstring _mapName)
{
	mapName = _mapName;
	vDropsItem.clear();
}

void Map::loadDoor(tstring Mapname)
{
	//Door정보 불러오기
	SDOOR tmpDoor[DOORMAX];
	for (int i = 0; i < DOORMAX; ++i) {
		tmpDoor[i].kind = EDOORKIND_NONE;
	}
	HANDLE file;
	DWORD read;
	tstring nameString = L"mapfile/" + Mapname + L"_door.map";
	tchar* name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, tmpDoor, sizeof(SDOOR) * DOORMAX, &read, NULL);
	CloseHandle(file);
	vDoor.clear();
	for (int i = 0; i < DOORMAX; ++i) {
		if (tmpDoor[i].kind == EDOORKIND_NONE) {
			break;
		}
		else {
			vDoor.push_back(new Door);
			vDoor.back()->init(tmpDoor[i], Mapname);
			vDoor.back()->setMemoryDogRect(*mDog->getRectMemory());
			vDoor.back()->setMemoryDogInven(*mDog->getInvenMemory());
		}
	}
}

void Map::loadEnemy(tstring Mapname)
{
	//Door정보 불러오기
	SENEMY tmpEnemy[ENEMYMAX];
	for (int i = 0; i < ENEMYMAX; ++i) {
		tmpEnemy[i].kind = EENEMYKIND_NONE;
	}
	HANDLE file;
	DWORD read;
	tstring nameString = L"mapfile/" + Mapname + L"_enemy.map";
	tchar* name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, tmpEnemy, sizeof(SENEMY) * ENEMYMAX, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < vEnemy.size(); ++i) {
		bulletCollision->deleteSomeThings(vEnemy.at(i)->getRectMemory(), vEnemy.at(i)->getIsAttackMemory(), vEnemy.at(i)->getIsDeleteMemory(), vEnemy.at(i)->getDamageMemory());
	}
	vEnemy.clear();
	for (int i = 0; i < ENEMYMAX; ++i) {
		tstring tmpName = tmpEnemy[i].name;
		if (tmpEnemy[i].kind == EENEMYKIND_NONE) {
			break;
		}
		else if (tmpName == L"1st_boss") {
			CAMERAMANAGER->setBossMode(true);
			Enemy_BOSS* ptmpBoss = new Enemy_BOSS;
			ptmpBoss->init(tmpEnemy[i], Mapname);
			ptmpBoss->setDogPositionMemory(mDog->getPoint());
			vEnemy.push_back(ptmpBoss);
			bulletCollision->addTheSomeThings(vEnemy.back()->getRectMemory(), vEnemy.back()->getIsAttackMemory(), vEnemy.back()->getIsDeleteMemory(), vEnemy.back()->getDamageMemory());
		}
		else {
			Enemy* ptmpEnemy = new Enemy;
			ptmpEnemy->init(tmpEnemy[i], Mapname);
			ptmpEnemy->setDogPositionMemory(mDog->getPoint());
			vEnemy.push_back(ptmpEnemy);
			bulletCollision->addTheSomeThings(vEnemy.back()->getRectMemory(), vEnemy.back()->getIsAttackMemory(), vEnemy.back()->getIsDeleteMemory(), vEnemy.back()->getDamageMemory());
		}
	}

}

void Map::loadObject(tstring Mapname)
{
	//Door정보 불러오기
	SOBJECT tmpObject[OBJECTMAX];
	for (int i = 0; i < OBJECTMAX; ++i) {
		tmpObject[i].kind = EOBJECTKIND_NONE;
	}
	HANDLE file;
	DWORD read;
	tstring nameString = L"mapfile/" + Mapname + L"_object.map";
	tchar* name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, tmpObject, sizeof(SOBJECT) * OBJECTMAX, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < vObject.size(); ++i) {
		if (vObject.at(i)->getImageName() == L"press" || vObject.at(i)->getImageName() == L"boxAbs") {
			vObject.at(i)->deleteRect();
		}
		else if (vObject.at(i)->getImageName() == L"box") {
			vObject.at(i)->deleteRect();
			bulletCollision->deleteSomeThings(&vObject.at(i)->getRect(), ((Object_BOX*)vObject.at(i))->getBoolMemory(), ((Object_BOX*)vObject.at(i))->getDeleteMemory(), ((Object_BOX*)vObject.at(i))->getDamageMemory());
		}
	}
	vObject.clear();
	for (int i = 0; i < OBJECTMAX; ++i) {
		if (tmpObject[i].kind == EOBJECTKIND_NONE) {
			break;
		}
		else {
			tstring tmp = tmpObject[i].name;
			if (tmp == L"spike" || tmp == L"press" || tmp == L"firePillar" || tmp == L"spike_up" || tmp == L"spike_left" || tmp == L"spike_right") {
				Object_DAMAGE* tmpDam = new Object_DAMAGE;
				tmpDam->init(tmpObject[i], Mapname);
				tmpDam->setMemoryDogRect(*mDog->getRectMemory());
				vObject.push_back(tmpDam);
				vObject.back()->setMemoryDogPoint(*mDog->getPoint());
				vObject.back()->setMemoryDog(mDog);
				if (tmpDam->getImageName() == L"press") {
					mDog->addObjectRect(&tmpDam->getRect());
				}
			}
			else if (tmp == L"depot" || tmp == L"depot_boots" || tmp == L"depot_card_red" || tmp == L"depot_card_white" || tmp == L"depot_card_green" || tmp == L"depot_card_blue") {
				Object_TOOL* tmpTool = new Object_TOOL;
				tmpTool->init(tmpObject[i], Mapname);
				tmpTool->setMemoryDogRect(*mDog->getRectMemory());
				tmpTool->setMemoryDogInven(*mDog->getInvenMemory());
				vObject.push_back(tmpTool);
				vObject.back()->setMemoryDogPoint(*mDog->getPoint());
			}
			else if (tmp == L"box") {
				Object_BOX* tmpTool = new Object_BOX;
				tmpTool->init(tmpObject[i], Mapname);
				tmpTool->setMemoryDogRect(*mDog->getRectMemory());
				tmpTool->setMemoryDogPoint(*mDog->getPoint());
				tmpTool->setMemoryDog(mDog);
				tmpTool->setvDropItem(&vDropsItem);
				mDog->addObjectRect(&tmpTool->getRect());
				bulletCollision->addTheSomeThings(&tmpTool->getRect(), ((Object_BOX*)tmpTool)->getBoolMemory(), ((Object_BOX*)tmpTool)->getDeleteMemory(), ((Object_BOX*)tmpTool)->getDamageMemory());
				vObject.push_back(tmpTool);
			}
			else if (tmp == L"health" || tmp == L"upgrade" || tmp == L"bullet") {
				Object_ITEM* tmpTool = new Object_ITEM;
				tmpTool->init(tmpObject[i], Mapname);
				tmpTool->setMemoryDogRect(*mDog->getRectMemory());
				tmpTool->setMemoryDogPoint(*mDog->getPoint());
				tmpTool->setMemoryDog(mDog);
				vObject.push_back(tmpTool);
			}
			else if (tmp == L"healmachine" || tmp == L"upgrademachine" || tmp == L"savemachine") {
				Object_VENDING* tmpVending = new Object_VENDING;
				tmpVending->init(tmpObject[i], Mapname);
				tmpVending->setMemoryDogRect(*mDog->getRectMemory());
				tmpVending->setMemoryDogPoint(*mDog->getPoint());
				tmpVending->setMemoryDog(mDog);
				vObject.push_back(tmpVending);
			}
			else {
				vObject.push_back(new Object);
				vObject.back()->init(tmpObject[i], Mapname);
				vObject.back()->setMemoryDogRect(*mDog->getRectMemory());
				vObject.back()->setMemoryDogPoint(*mDog->getPoint());
				vObject.back()->setMemoryDog(mDog);
				if (tmp == L"boxAbs") {
					mDog->addObjectRect(&vObject.back()->getRect());
				}
			}
		}
	}
}

void Map::loadElevator(tstring Mapname)
{

	SELEVATOR tmpElevator[ELEVATORMAX];
	HANDLE file;
	DWORD read;
	tstring nameString = L"mapfile/" + Mapname + L"_elevator.map";
	tchar* name = (wchar_t *)nameString.c_str();
	file = CreateFile(name,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	ReadFile(file, tmpElevator, sizeof(SELEVATOR) * ELEVATORMAX, &read, NULL);
	CloseHandle(file);
	for (int i = 0; i < vElevator.size(); ++i) {
		vElevator.at(i)->deleteRect();
	}
	vElevator.clear();
	for (int i = 0; i < ELEVATORMAX; ++i) {
		if (tmpElevator[i].state >= EMAKEELEVATOR_SWITCHSET1) {
			Elevator* tmpEle = new Elevator;
			tmpEle->init(tmpElevator[i], Mapname);
			tmpEle->setMemoryDog(mDog);
			vElevator.push_back(tmpEle);
			mDog->addObjectRect(&tmpEle->getRect());
		}
		else break;
	}
}

void Map::loadSaveData(sSaveData& data)
{
	SOUNDMANAGER->allsoundStop();
	if (!SOUNDMANAGER->isPlaySound("gameBGM2")) {
		SOUNDMANAGER->play("gameBGM2", 1.0f * bgmSound);
	}
	CAMERAMANAGER->setBossMode(false);
	mDog->loadData(data);
}

void Map::deadSoGoBack()
{
	SOUNDMANAGER->allsoundStop();
	if (!SOUNDMANAGER->isPlaySound("gameBGM2")) {
		SOUNDMANAGER->play("gameBGM2", 1.0f * bgmSound);
	}
	CAMERAMANAGER->setBossMode(false);
	tchar tmpStr[30];
	wsprintf(tmpStr, L"%d.save", saveDataNum);
	if (_waccess_s(tmpStr, 0) == 0) {
		sSaveData tmpData;
		HANDLE file;
		DWORD read;
		file = CreateFile(tmpStr,
			GENERIC_READ,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		ReadFile(file, &tmpData, sizeof(sSaveData), &read, NULL);
		CloseHandle(file);

		time = 0;
		changeMap(tmpData.mapName);
		mDog->loadData(tmpData);
		loadEnemy(mapName);
		loadDoor(mapName);
		loadElevator(mapName);
		loadObject(mapName);
	}
	else {
		SCENEMANAGER->changeScene("menuSC");
	}
}
