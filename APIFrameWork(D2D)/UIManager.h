#pragma once
#include "gameNode.h"
#include "progressBar.h"

class UIManager : public gameNode
{
private:
	progressBar* hpBar;
	progressBar* upgradeBar;
	int* money;
	int* maxHP;
	int* currentHP;
	vector<EINVENITEM>* dogInvetory;
	SDOGWEAPONINFO* dogWeapon;

public:
	UIManager();
	~UIManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMemoryMoney(int& _money) { money = &_money; }
	void setMemoryHP(int& _max, int& _current) { maxHP = &_max; currentHP = &_current; }
	void setMemoryDogInven(vector<EINVENITEM>& Invetory) { dogInvetory = &Invetory; }
	void setMemoryDogWeapon(SDOGWEAPONINFO& _weapon) { dogWeapon = &_weapon; }
};