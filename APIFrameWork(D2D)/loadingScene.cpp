#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init(void)
{
	_loading = new loading;
	_loading->init();

	this->totalLoading();
	return S_OK;;
}

void loadingScene::release(void)
{
}

void loadingScene::update(void)
{
	_loading->update();
	if (_loading->loadingDone()) {

		//강아지ani
		{
			ANIMATIONMANAGER->addDefAnimation(L"dog_die", L"Dog_dead", 8, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"jumpEffect", L"jumpEffect", 10, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_idle", L"Dog_none_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_run", L"Dog_none_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_jump_ready", L"Dog_none_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_jump_ing", L"Dog_none_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_fall_ing", L"Dog_none_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_none_fall_end", L"Dog_none_fall_end", 15, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_idle_up", L"Dog_club_idle_up", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_run_up", L"Dog_club_run_up", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_idle", L"Dog_club_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_run", L"Dog_club_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_jump_ready", L"Dog_club_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_jump_ing", L"Dog_club_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_fall_ing", L"Dog_club_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_fall_end", L"Dog_club_fall_end", 15, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_attack", L"Dog_club_attack", 10, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_club_attack_up", L"Dog_club_attack_up", 10, false, false);

			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_idle_up", L"Dog_gun_idle_up", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_run_up", L"Dog_gun_run_up", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_idle", L"Dog_gun_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_run", L"Dog_gun_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_jump_ready", L"Dog_gun_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_jump_ing", L"Dog_gun_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_fall_ing", L"Dog_gun_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_gun_fall_end", L"Dog_gun_fall_end", 15, false, false);

			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_idle_up", L"Dog_shotgun_idle_up", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_run_up", L"Dog_shotgun_run_up", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_idle", L"Dog_shotgun_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_run", L"Dog_shotgun_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_jump_ready", L"Dog_shotgun_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_jump_ing", L"Dog_shotgun_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_fall_ing", L"Dog_shotgun_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_shotgun_fall_end", L"Dog_shotgun_fall_end", 15, false, false);

			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_idle_up", L"Dog_plasma_idle_up", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_run_up", L"Dog_plasma_run_up", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_idle", L"Dog_plasma_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_run", L"Dog_plasma_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_jump_ready", L"Dog_plasma_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_jump_ing", L"Dog_plasma_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_fall_ing", L"Dog_plasma_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_plasma_fall_end", L"Dog_plasma_fall_end", 15, false, false);

			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_idle_up", L"Dog_rocket_idle_up", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_run_up", L"Dog_rocket_run_up", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_idle", L"Dog_rocket_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_run", L"Dog_rocket_run", 12, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_jump_ready", L"Dog_rocket_jump_ready", 30, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_jump_ing", L"Dog_rocket_jump_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_fall_ing", L"Dog_rocket_fall_ing", 7, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"dog_rocket_fall_end", L"Dog_rocket_fall_end", 15, false, false);
		}

		//object Animation
		{
			ANIMATIONMANAGER->addDefAnimation(L"DoorOpen", L"door_opening", 8, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"escalator", L"escalator", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"firePillar", L"firePillar", 9, false, false);
			ANIMATIONMANAGER->addDefAnimation(L"healmachine", L"healmachine", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"upgrademachine", L"upgrademachine", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"savemachine", L"savemachine", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"healmachine_active", L"healmachine_active", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"upgrademachine_active", L"upgrademachine_active", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"savemachine_active", L"savemachine_active", 8, false, true);
		}

		//enemyAnimation
		{
			ANIMATIONMANAGER->addDefAnimation(L"slime_green_damage", L"slime_green_damage", 15, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"spider_damage", L"spider_damage", 15, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"rat_damage", L"rat_damage", 15, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"egg_damage", L"egg_damage", 10, false, true);

			ANIMATIONMANAGER->addDefAnimation(L"1st_boss_idle", L"1st_boss_idle", 8, false, true);
			ANIMATIONMANAGER->addDefAnimation(L"1st_boss_die", L"1st_boss_die", 8, false, false); 
		}

		//bulletEffect
		{
			EFFECTMANAGER->addEffect(L"gun_flash", L"gun_flash", 132 * 2, 24 * 2, 132 * 2 / 4, 24 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"gun_flash_left", L"gun_flash_left", 132 * 2, 24 * 2, 132 * 2 / 4, 24 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"gun_flash_up", L"gun_flash_up", 132 * 2, 50 * 2, 132 * 2 / 4, 50 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"gun_flash_down", L"gun_flash_down", 132 * 2, 50 * 2, 132 * 2 / 4, 50 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"rocket_flash", L"rocket_flash", 188 * 2, 32 * 2, 188 * 2 / 4, 32 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"rocket_flash_left", L"rocket_flash_left", 188 * 2, 32 * 2, 188 * 2 / 4, 32 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"rocket_flash_up", L"rocket_flash_up", 188 * 2, 32 * 2, 188 * 2 / 4, 32 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"rocket_flash_down", L"rocket_flash_down", 188 * 2, 32 * 2, 188 * 2 / 4, 32 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"shotgun_flash", L"shotgun_flash", 120 * 2, 21 * 2, 120 * 2 / 4, 21 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"shotgun_flash_left", L"shotgun_flash_left", 120 * 2, 31 * 2, 120 * 2 / 4, 31 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"shotgun_flash_up", L"shotgun_flash_up", 120 * 2, 31 * 2, 120 * 2 / 4, 31 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"shotgun_flash_down", L"shotgun_flash_down", 120 * 2, 31 * 2, 120 * 2 / 4, 31 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"plasma_flash", L"plasma_flash", 141 * 2, 35 * 2, 141 * 2 / 3, 35 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"plasma_flash_left", L"plasma_flash_left", 141 * 2, 35 * 2, 141 * 2 / 3, 35 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"plasma_flash_up", L"plasma_flash_up", 141 * 2, 35 * 2, 141 * 2 / 3, 35 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"plasma_flash_down", L"plasma_flash_down", 141 * 2, 35 * 2, 141 * 2 / 3, 35 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"gun_destroy", L"gun_destroy", 132 * 2, 24 * 2, 132 * 2 / 4, 24 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"rocket_destroy", L"rocket_destroy", 188 * 2, 31 * 2, 188 * 2 / 4, 31 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"shotgun_destroy", L"shotgun_destroy", 90 * 2, 20 * 2, 90 * 2 / 3, 20 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"plasma_destroy", L"plasma_destroy", 141 * 2, 35 * 2, 141 * 2 / 3, 35 * 2, 1, 0.3f, 100);

		EFFECTMANAGER->addEffect(L"bullet_hit", L"bullet_hit", 140 * 2, 27 * 2, 140 * 2 / 5, 27 * 2, 1, 0.3f, 100);
		EFFECTMANAGER->addEffect(L"Dam", L"Dam", 126 * 2, 23 * 2, 126 * 2 / 6, 23 * 2, 1, 0.3f, 100);
		}

		//sounds
		{
			SOUNDMANAGER->addSound("mainBGM", "sounds/mainBGM.wav", true, true);
			SOUNDMANAGER->addSound("clickSound", "sounds/clickSound.mp3", false, false);
			SOUNDMANAGER->addSound("club", "sounds/club.mp3", false, false);
			SOUNDMANAGER->addSound("gun", "sounds/gun.mp3", false, false);
			SOUNDMANAGER->addSound("jump", "sounds/jump.mp3", false, false);
			SOUNDMANAGER->addSound("land", "sounds/land.mp3", false, false);
			SOUNDMANAGER->addSound("walk", "sounds/walk.mp3", false, true);
			SOUNDMANAGER->addSound("event", "sounds/heal.mp3", false, false);
			SOUNDMANAGER->addSound("save", "sounds/save.mp3", false, false);
			SOUNDMANAGER->addSound("textOut", "sounds/textOut.mp3", false, false);
			SOUNDMANAGER->addSound("door", "sounds/door.mp3", false, false);
			SOUNDMANAGER->addSound("switch", "sounds/switch.wav", false, false);
			SOUNDMANAGER->addSound("elevatorStart", "sounds/elevator.mp3", false, false);
			SOUNDMANAGER->addSound("elevatorloop", "sounds/elevatorLoop.mp3", false, true);
			SOUNDMANAGER->addSound("elevatorEnd", "sounds/elevatorEnd.mp3", false, false);
			SOUNDMANAGER->addSound("coin", "sounds/coin.wav", false, false);
			SOUNDMANAGER->addSound("slimeDeath", "sounds/slimeDeath.wav", false, false);
			SOUNDMANAGER->addSound("hit_bullet", "sounds/hit_bullet.mp3", false, false);
			SOUNDMANAGER->addSound("hit_club", "sounds/hit_club.wav", false, false);
			SOUNDMANAGER->addSound("Dogdamage", "sounds/Dogdamage.wav", false, false);
			SOUNDMANAGER->addSound("bossIntro", "sounds/bossIntro.wav", true, false);
			SOUNDMANAGER->addSound("bossMove", "sounds/bossMove.mp3", false, true);
			SOUNDMANAGER->addSound("slugDown", "sounds/SlugDown.wav", false, false);
			SOUNDMANAGER->addSound("bossDeath", "sounds/bossDeath.wav", false, false);
			SOUNDMANAGER->addSound("Rocket", "sounds/Rocket.wav", false, false);
			SOUNDMANAGER->addSound("Blaster", "sounds/Blaster.wav", false, false);
			SOUNDMANAGER->addSound("bumb", "sounds/bumb.mp3", false, false);
			SOUNDMANAGER->addSound("ArachnideDie", "sounds/ArachnideDie.wav", false, false);
			SOUNDMANAGER->addSound("ArachnideSpawn", "sounds/ArachnideSpawn.wav", false, false);
			SOUNDMANAGER->addSound("gameBGM2", "sounds/gameBGM2.mp3", true, true);
			SOUNDMANAGER->addSound("escalator", "sounds/escalator.mp3", false, true);
			SOUNDMANAGER->addSound("FireFlame", "sounds/FireFlame.wav", false, false);
			SOUNDMANAGER->addSound("laser", "sounds/laser.mp3", false, true);
			SOUNDMANAGER->addSound("start", "sounds/start.wav", false, false);
			SOUNDMANAGER->addSound("boxBreak", "sounds/boxBreak.wav", false, false);
			SOUNDMANAGER->addSound("plasmagun", "sounds/plasmagun.wav", false, false);
			SOUNDMANAGER->addSound("bossBGM", "sounds/bossBGM.mp3", false, true);

		}
		SCENEMANAGER->changeScene("menuSC");
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

void loadingScene::totalLoading()
{
	//메뉴씬
	_loading->loadImage(L"mainmenuBG", L"images/UI/main.png", 0, 0, 1280, 720, false);
	_loading->loadImage(L"buttonNone", L"images/UI/buttonnone.png", 0, 0, 170, 38, true);
	_loading->loadImage(L"buttonDown", L"images/UI/buttondown.png", 0, 0, 170, 38, true);
	_loading->loadImage(L"buttonUp", L"images/UI/buttonup.png", 0, 0, 170, 38, true);

	//헬프신
	_loading->loadImage(L"helpBG", L"images/UI/helpBG.png", 0, 0, 1280, 720, false);

	//셀렉트신
	_loading->loadImage(L"choiceBG", L"images/UI/choiceBG.png", 0, 0, 1280, 720, false);

	//레빌신
	_loading->loadImage(L"levelBG", L"images/UI/levelBG.png", 0, 0, 1280, 720, false);

	//사운드신
	_loading->loadImage(L"soundBG", L"images/UI/soundBG.png", 0, 0, 1280, 720, false);
	_loading->loadImage(L"music", L"images/UI/music_0.png", 0, 0, 10, 20, false);

	//인게임(맵)
	_loading->loadImage(L"start_00", L"images/map/start/start_00.png", 0, 0, 2048, 1024, false);
	_loading->loadImage(L"start_01", L"images/map/start/start_01.png", 0, 0, 1152, 1472, false);
	_loading->loadImage(L"thePit_00", L"images/map/thePit/the_pit_00_complete.png", 0, 0, 6400  *2, 2*2848, false);
	_loading->loadImage(L"thePit_01", L"images/map/thePit/the_pit_01_complete.png", 0, 0, 960	*2, 2*544, false);
	_loading->loadImage(L"thePit_02", L"images/map/thePit/the_pit_02_complete.png", 0, 0, 768	*2, 2*544, false);
	_loading->loadImage(L"thePit_03", L"images/map/thePit/the_pit_03_complete.png", 0, 0, 768	*2, 2*544, false);
	_loading->loadImage(L"thePit_04", L"images/map/thePit/the_pit_04_complete.png", 0, 0, 896	*2, 2*352, false);
	_loading->loadImage(L"thePit_05", L"images/map/thePit/the_pit_05_complete.png", 0, 0, 736	*2, 2*448, false);
	_loading->loadImage(L"thePit_06", L"images/map/thePit/the_pit_06_complete.png", 0, 0, 768	*2, 2*736, false);
	_loading->loadImage(L"thePit_07", L"images/map/thePit/the_pit_07_complete.png", 0, 0, 768	*2, 2*544, false);
	_loading->loadImage(L"thePit_08", L"images/map/thePit/the_pit_08_complete.png", 0, 0, 448	*2, 2*256, false);
	_loading->loadImage(L"thePit_09", L"images/map/thePit/the_pit_09_complete.png", 0, 0, 1728	*2, 2*704, false);
	_loading->loadImage(L"thePit_10", L"images/map/thePit/the_pit_10_complete.png", 0, 0, 2240	*2, 2*3872, false);
	_loading->loadImage(L"thePit_11", L"images/map/thePit/the_pit_11_complete.png", 0, 0, 1888	*2, 2*608, false);

	_loading->loadImage(L"thePit", L"images/UI/save/thePit.png", 0, 0, 180, 180, false);

	//인게임(UI)
	_loading->loadImage(L"inventory", L"images/UI/ingame/inventory.png", WINSIZEX_NUM / 2, WINSIZEY_NUM - 33, 602, 66, true);
	_loading->loadImage(L"dog_info", L"images/UI/ingame/ui_v2 (1).png", 40, 0, 344, 168, false);
	_loading->loadImage(L"healthbar", L"images/UI/ingame/HealthBar.png", 0, 0, 164, 18, false);
	_loading->loadImage(L"weaponbar", L"images/UI/ingame/WeaponBar.png", 0, 0, 164, 18, false);

	_loading->loadImage(L"bossbar_front", L"images/UI/ingame/bossbar_front.png", 0, 0, 359 * 2, 7 * 2, false);
	_loading->loadImage(L"bossbar_back", L"images/UI/ingame/bossbar_back.png", 260, WINSIZEY_NUM - 130, 377 * 2, 25 * 2, false);

	_loading->loadImage(L"boots", L"images/herodog/inventory/boots.png", 0, 0, 32, 32, true);
	_loading->loadImage(L"bluecard", L"images/herodog/inventory/blue_card_v1.png", 0, 0, 32, 28, true);
	_loading->loadImage(L"greencard", L"images/herodog/inventory/green_c_v1.png", 0, 0, 32, 28, true);
	_loading->loadImage(L"redcard", L"images/herodog/inventory/red_card_v1.png", 0, 0, 32, 28, true);
	_loading->loadImage(L"whitecard", L"images/herodog/inventory/simple_card_v1.png", 0, 0, 32, 28, true);
	_loading->loadImage(L"tool", L"images/herodog/inventory/Tool.png", 0, 0, 32, 32, true);

	_loading->loadImage(L"ui_club", L"images/herodog/weapon/weapon_1.png", 54, 90, 68, 26, false);
	_loading->loadImage(L"ui_gun", L"images/herodog/weapon/weapon_2.png", 54, 90, 68, 26, false);
	_loading->loadImage(L"ui_shotgun", L"images/herodog/weapon/weapon_3.png", 54, 90, 68, 26, false);
	_loading->loadImage(L"ui_rocket", L"images/herodog/weapon/weapon_4.png", 54, 90, 68, 26, false);
	_loading->loadImage(L"ui_plasma", L"images/herodog/weapon/weapon_5.png", 54, 90, 68, 26, false);

	_loading->loadImage(L"popUp", L"images/UI/popup.png", WINSIZEX_NUM/2, WINSIZEY_NUM / 2, 200, 300, true);
	

	//인게임(캐릭터)
	_loading->loadFrameImage(L"Dog_dead", L"images/herodog/Hero_Die.png", 0, 0, 708, 70, 6, 1, true);
	_loading->loadFrameImage(L"jumpEffect", L"images/herodog/jumpEffect.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 268, 40, 3, 1, true);

	_loading->loadFrameImage(L"Dog_none_run", L"images/herodog/Hero_none_Run.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_none_idle", L"images/herodog/Hero_none_Idle.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_none_jump_ready", L"images/herodog/Hero_none_Jump_Ready.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_none_jump_ing", L"images/herodog/Hero_none_Jump_Ing.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_none_fall_ing", L"images/herodog/Hero_none_Fall_Ing.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_none_fall_end", L"images/herodog/Hero_none_Fall_End.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	
	_loading->loadImage(	 L"Dog_club_up",		L"images/herodog/Hero_club_up.png",					WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 92, 68, true);
	_loading->loadImage(	 L"Dog_club_down",		L"images/herodog/Hero_club_down.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 88, 104, true);
	_loading->loadFrameImage(L"Dog_club_run",		L"images/herodog/Hero_club_Run.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 1120, 74, 8, 1, true);
	_loading->loadFrameImage(L"Dog_club_idle",		L"images/herodog/Hero_club_Idle.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 480, 70, 4, 1, true);
	_loading->loadFrameImage(L"Dog_club_run_up",	L"images/herodog/Hero_club_Run_up.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 1120, 74, 8, 1, true);
	_loading->loadFrameImage(L"Dog_club_idle_up",	L"images/herodog/Hero_club_Idle_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 480, 70, 4, 1, true);
	_loading->loadFrameImage(L"Dog_club_jump_ready",L"images/herodog/Hero_club_Jump_Ready.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_club_jump_ing",	L"images/herodog/Hero_club_Jump_Ing.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 78, 3, 1, true);
	_loading->loadFrameImage(L"Dog_club_fall_ing",	L"images/herodog/Hero_club_Fall_Ing.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_club_fall_end",	L"images/herodog/Hero_club_Fall_End.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_club_attack",	L"images/herodog/Hero_Hit.png",						WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 198*2, 35*2, 2, 1, true);
	_loading->loadFrameImage(L"Dog_club_attack_up", L"images/herodog/Hero_Hit_up.png",					WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 272*2, 48*2, 2, 1, true);

	_loading->loadImage(	 L"Dog_gun_up",			L"images/herodog/Hero_gun_up.png",					WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 62, 68, true);
	_loading->loadImage(	 L"Dog_gun_down",		L"images/herodog/Hero_gun_down.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 88, 104, true);
	_loading->loadFrameImage(L"Dog_gun_run",		L"images/herodog/Hero_gun_Run.png",					WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_gun_idle",		L"images/herodog/Hero_gun_Idle.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_gun_run_up",		L"images/herodog/Hero_gun_Run_up.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_gun_idle_up",	L"images/herodog/Hero_gun_Idle_up.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_gun_jump_ready", L"images/herodog/Hero_gun_Jump_Ready.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_gun_jump_ing",	L"images/herodog/Hero_gun_Jump_Ing.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 78, 3, 1, true);
	_loading->loadFrameImage(L"Dog_gun_fall_ing",	L"images/herodog/Hero_gun_Fall_Ing.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_gun_fall_end",	L"images/herodog/Hero_gun_Fall_End.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);

	
	_loading->loadImage(	 L"Dog_rocket_up",			L"images/herodog/Hero_rocket_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 62, 78, true);
	_loading->loadImage(	 L"Dog_rocket_down",		L"images/herodog/Hero_rocket_down.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 88, 104, true);
	_loading->loadFrameImage(L"Dog_rocket_run",			L"images/herodog/Hero_rocket_Run.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_idle",		L"images/herodog/Hero_rocket_Idle.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 320, 70, 4, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_run_up",		L"images/herodog/Hero_rocket_Run_up.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_idle_up",		L"images/herodog/Hero_rocket_Idle_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_jump_ready",	L"images/herodog/Hero_rocket_Jump_Ready.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_jump_ing",	L"images/herodog/Hero_rocket_Jump_Ing.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 78, 3, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_fall_ing",	L"images/herodog/Hero_rocket_Fall_Ing.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_rocket_fall_end",	L"images/herodog/Hero_rocket_Fall_End.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	
	_loading->loadImage(	 L"Dog_shotgun_up",			L"images/herodog/Hero_shotgun_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 62, 78, true);
	_loading->loadImage(	 L"Dog_shotgun_down",		L"images/herodog/Hero_shotgun_down.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 88, 104, true);
	_loading->loadFrameImage(L"Dog_shotgun_run",		L"images/herodog/Hero_shotgun_Run.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_idle",		L"images/herodog/Hero_shotgun_Idle.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 320, 70, 4, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_run_up",		L"images/herodog/Hero_shotgun_Run_up.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_idle_up",	L"images/herodog/Hero_shotgun_Idle_up.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_jump_ready", L"images/herodog/Hero_shotgun_Jump_Ready.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_jump_ing",	L"images/herodog/Hero_shotgun_Jump_Ing.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 78, 3, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_fall_ing",	L"images/herodog/Hero_shotgun_Fall_Ing.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_shotgun_fall_end",	L"images/herodog/Hero_shotgun_Fall_End.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	
	_loading->loadImage(	 L"Dog_plasma_up",			L"images/herodog/Hero_plasma_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 62, 78, true);
	_loading->loadImage(	 L"Dog_plasma_down",		L"images/herodog/Hero_plasma_down.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 88, 104, true);
	_loading->loadFrameImage(L"Dog_plasma_run",			L"images/herodog/Hero_plasma_Run.png",				WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_idle",		L"images/herodog/Hero_plasma_Idle.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 320, 70, 4, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_run_up",		L"images/herodog/Hero_plasma_Run_up.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 656, 82, 8, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_idle_up",		L"images/herodog/Hero_plasma_Idle_up.png",			WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 280, 86, 4, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_jump_ready",	L"images/herodog/Hero_plasma_Jump_Ready.png",	WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 74, 3, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_jump_ing",	L"images/herodog/Hero_plasma_Jump_Ing.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 264, 78, 3, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_fall_ing",	L"images/herodog/Hero_plasma_Fall_Ing.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);
	_loading->loadFrameImage(L"Dog_plasma_fall_end",	L"images/herodog/Hero_plasma_Fall_End.png",		WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 176, 74, 2, 1, true);

	_loading->loadImage(L"redHeart", L"images/effect/redHeart.png", 0, 0, 1280, 720, false);
	//인게임(Door)
	_loading->loadImage(L"door_idle", L"images/Object/Door/doorCantOpen.png", 0, 0, 112, 106, true);
	_loading->loadImage(L"door_active", L"images/Object/Door/doorCantOpen_active.png", 0, 0, 112, 106, true);
	_loading->loadImage(L"door_break_idle", L"images/Object/Door/doorBreakOpen.png", 0, 0, 112, 106, true);
	_loading->loadImage(L"door_break_active", L"images/Object/Door/doorBreakOpen_active.png", 0, 0, 112, 106, true);
	_loading->loadImage(L"vent_close_idle", L"images/Object/Door/vent.png", 0, 0, 68, 66, true);
	_loading->loadImage(L"vent_close_active", L"images/Object/Door/vent(active).png", 0, 0, 72, 68, true);
	_loading->loadImage(L"vent_open_idle", L"images/Object/Door/vent2.png", 0, 0, 68, 66, true);
	_loading->loadImage(L"vent_open_active", L"images/Object/Door/vent2(active).png", 0, 0, 72, 68, true);
	_loading->loadFrameImage(L"door_opening", L"images/Object/Door/doorOpen.png", 0, 0, 1044, 106, 9, 1, true);

	//인게임(Object)
	_loading->loadFrameImage(L"healmachine", L"images/Object/Object_vendingMachine/heal.png", 0, 0, 216 * 2, 61 * 2, 4, 1, true);
	_loading->loadFrameImage(L"upgrademachine", L"images/Object/Object_vendingMachine/upgrade.png", 0, 0, 216 * 2, 61 * 2, 4, 1, true);
	_loading->loadFrameImage(L"savemachine", L"images/Object/Object_vendingMachine/save.png", 0, 0, 168 * 2, 61 * 2, 4, 1, true);
	_loading->loadFrameImage(L"healmachine_active", L"images/Object/Object_vendingMachine/heal_active.png", 0, 0, 216 * 2, 61 * 2, 4, 1, true);
	_loading->loadFrameImage(L"upgrademachine_active", L"images/Object/Object_vendingMachine/upgrade_active.png", 0, 0, 216 * 2, 61 * 2, 4, 1, true);
	_loading->loadFrameImage(L"savemachine_active", L"images/Object/Object_vendingMachine/save_active.png", 0, 0, 168 * 2, 61 * 2, 4, 1, true);

	_loading->loadImage(L"box",				L"images/Object/Object_canBreak/box_0.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"box_flag",		L"images/Object/Object_canBreak/box_Frag.png", 0, 0, 56*2, 21*2, true);
	_loading->loadImage(L"boxAbs",			L"images/Object/Object_none/box_7.png", 0, 0, 68, 46, true);
	_loading->loadImage(L"depot",			L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_boots", L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_card_red", L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_card_white", L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_card_green", L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_card_blue", L"images/Object/Object_operation/box_9.png", 0, 0, 72, 44, true);
	_loading->loadImage(L"depot_active",	L"images/Object/Object_operation/box(active).png", 0, 0, 76, 46, true);
	_loading->loadImage(L"pc_1",			L"images/Object/Object_none/pc_1.png", 0, 0, 108, 62, true);
	_loading->loadImage(L"electr_1",		L"images/Object/Object_none/electr1.png", 0, 0, 94, 92, true);
	_loading->loadImage(L"monitorv_1",		L"images/Object/Object_none/monitorv1_7_2.png", 0, 0, 64, 64, true);
	_loading->loadImage(L"monitorv_2",		L"images/Object/Object_none/monitorv8.png", 0, 0, 68, 46, true);
	_loading->loadImage(L"capsule_eo42",	L"images/Object/Object_none/capsule_eo42_1.png", 0, 0, 224, 136, true);
	_loading->loadImage(L"capsule_eo43",	L"images/Object/Object_none/capsule_eo43_1.png", 0, 0, 224, 138, true);
	_loading->loadImage(L"shelf",			L"images/Object/Object_none/env_2.png", 0, 0, 50, 64, true);
	_loading->loadFrameImage(L"escalator",	L"images/Object/Object_none/escalator.png", 0, 0, 192*2, 10, 6, 1, true);
	_loading->loadImage(L"cctv",			L"images/Object/Object_none/vid_cam5.png", 0, 0, 40, 40, true);
	_loading->loadImage(L"spike",			L"images/Object/Object_none/spikes.png", 0, 0, 64, 32, true);
	_loading->loadImage(L"spike_up", L"images/Object/Object_none/spikes_up.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 64, 32, true);
	_loading->loadImage(L"spike_right", L"images/Object/Object_none/spikes_right.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 32, 64, true);
	_loading->loadImage(L"spike_left", L"images/Object/Object_none/spikes_left.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 32, 64, true);
	_loading->loadImage(L"press",			L"images/Object/press_0.png", 0, 0, 62*2, 96*2, true);
	_loading->loadFrameImage(L"firePillar",	L"images/Object/firepillar.png", 0, 0, 480 * 2, 96*2, 15, 1, true);
	_loading->loadImage(L"health", L"images/Object/health.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"bullet", L"images/Object/bullet.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"upgrade", L"images/Object/upgrade.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"health_active", L"images/Object/health_active.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"bullet_active", L"images/Object/bullet_active.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"upgrade_active", L"images/Object/upgrade_active.png", 0, 0, 60, 30, true);
	_loading->loadImage(L"drain", L"images/Object/drain.png", 0, 0, 28*2, 16*2, true);

	//인게임(Elevator)
	_loading->loadImage(L"panel_active", L"images/object/panel(active).png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 21 * 2, 31 * 2, true);
	_loading->loadImage(L"panel", L"images/object/panel.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 19 * 2, 29 * 2, true);
	_loading->loadImage(L"lift_small", L"images/object/lift.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 32 * 2, 11 * 2, true);
	_loading->loadImage(L"lift_middle", L"images/object/lift_x96.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 96 * 2, 11 * 2, true);
	_loading->loadImage(L"laser", L"images/object/laser.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 9 * 2, 18 * 2, true);

	//인게임 드랍아이템
	_loading->loadImage(L"ammo", L"images/Object/drop/ammo.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 12 * 2, 9 * 2, true);
	_loading->loadImage(L"bone", L"images/Object/drop/bone_v3.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 15 * 2, 8 * 2, true);
	_loading->loadImage(L"money", L"images/Object/drop/MutagenV2.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 16 * 2, 7 * 2, true);


	//총알이미지
	_loading->loadFrameImage(L"gun_bullet", L"images/bullet/gun_bullet.png", 0, 0, 81 * 2, 15 * 2, 3, 3, true);
	_loading->loadFrameImage(L"rocket_bullet", L"images/bullet/rocket_bullet.png", 0, 0, 132 * 2, 27 * 2, 3, 3, true);
	_loading->loadFrameImage(L"shotgun_bullet", L"images/bullet/shotgun_bullet.png", 0, 0, 116 * 2, 40 * 2, 4, 3, true);
	_loading->loadFrameImage(L"plasma_bullet", L"images/bullet/plasma_bullet.png", 0, 0, 33 * 2, 33 * 2, 3, 3, true);

	_loading->loadFrameImage(L"gun_flash", L"images/effect/gun_flash.png", 0, 0, 132 * 2, 24 * 2, 4, 1, true);
	_loading->loadFrameImage(L"gun_flash_left", L"images/effect/gun_flash_left.png", 0, 0, 132 * 2, 24 * 2, 4, 1, true);
	_loading->loadFrameImage(L"gun_flash_up", L"images/effect/gun_flash_up.png", 0, 0, 132 * 2, 50 * 2, 4, 1, true);
	_loading->loadFrameImage(L"gun_flash_down", L"images/effect/gun_flash_down.png", 0, 0, 132 * 2, 50 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rocket_flash", L"images/effect/rocket_flash.png", 0, 0, 188 * 2, 32 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rocket_flash_left", L"images/effect/rocket_flash_left.png", 0, 0, 188 * 2, 32 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rocket_flash_up", L"images/effect/rocket_flash_up.png", 0, 0, 188 * 2, 32 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rocket_flash_down", L"images/effect/rocket_flash_down.png", 0, 0, 188 * 2, 32 * 2, 4, 1, true);
	_loading->loadFrameImage(L"shotgun_flash", L"images/effect/shotgun_flash.png", 0, 0, 120 * 2, 21 * 2, 4, 1, true);
	_loading->loadFrameImage(L"shotgun_flash_left", L"images/effect/shotgun_flash_left.png", 0, 0, 120 * 2, 31 * 2, 4, 1, true);
	_loading->loadFrameImage(L"shotgun_flash_up", L"images/effect/shotgun_flash_up.png", 0, 0, 120 * 2, 31 * 2, 4, 1, true);
	_loading->loadFrameImage(L"shotgun_flash_down", L"images/effect/shotgun_flash_down.png", 0, 0, 120 * 2, 31 * 2, 4, 1, true);
	_loading->loadFrameImage(L"plasma_flash", L"images/effect/plasma_flash.png", 0, 0, 141 * 2, 35 * 2, 3, 1, true);
	_loading->loadFrameImage(L"plasma_flash_left", L"images/effect/plasma_flash_left.png", 0, 0, 141 * 2, 35 * 2, 3, 1, true);
	_loading->loadFrameImage(L"plasma_flash_up", L"images/effect/plasma_flash_up.png", 0, 0, 141 * 2, 35 * 2, 3, 1, true);
	_loading->loadFrameImage(L"plasma_flash_down", L"images/effect/plasma_flash_down.png", 0, 0, 141 * 2, 35 * 2, 3, 1, true);

	_loading->loadFrameImage(L"gun_destroy", L"images/effect/gun_destroy.png", 0, 0, 132 * 2, 24 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rocket_destroy", L"images/effect/rocket_destroy.png", 0, 0, 188 * 2, 31 * 2, 4, 1, true);
	_loading->loadFrameImage(L"shotgun_destroy", L"images/effect/shotgun_destroy.png", 0, 0, 90 * 2, 20 * 2, 3, 1, true);
	_loading->loadFrameImage(L"plasma_destroy", L"images/effect/plasma_destroy.png", 0, 0, 141 * 2, 35 * 2, 3, 1, true);

	_loading->loadFrameImage(L"bullet_hit", L"images/effect/bullet_hit.png", 0, 0, 140 * 2, 27 * 2, 5, 1, true);
	_loading->loadFrameImage(L"Dam", L"images/effect/Dam.png", 0, 0, 126 * 2, 23 * 2, 6, 1, true);

	//enemies
	_loading->loadFrameImage(L"slime_green_idle", L"images/enemy/slime_green_idle.png", 0, 0, 172 * 2, 26 * 2, 4, 1, true);
	_loading->loadFrameImage(L"slime_green_damage", L"images/enemy/slime_green_damage.png", 0, 0, 86 * 2, 26 * 2, 2, 1, true);
	_loading->loadFrameImage(L"slime_green_death", L"images/enemy/slime_green_death.png", 0, 0, 215 * 2, 25 * 2, 5, 1, true);
	_loading->loadFrameImage(L"spider_idle", L"images/enemy/spider_idle.png", 0, 0, 420 * 2, 31 * 2, 5, 1, true);
	_loading->loadFrameImage(L"spider_move", L"images/enemy/spider_move.png", 0, 0, 342 * 2, 30 * 2, 6, 1, true);
	_loading->loadFrameImage(L"spider_damage", L"images/enemy/spider_damage.png", 0, 0, 168 * 2, 30 * 2, 2, 1, true);
	_loading->loadFrameImage(L"spider_death", L"images/enemy/spider_death.png", 0, 0, 390 * 2, 38 * 2, 6, 1, true);

	_loading->loadFrameImage(L"rat_idle", L"images/enemy/Rat-idle.png", 0, 0, 260 * 2, 32 * 2, 4, 1, true);
	_loading->loadFrameImage(L"rat_move", L"images/enemy/Rat-move.png", 0, 0, 390 * 2, 34 * 2, 6, 1, true);
	_loading->loadFrameImage(L"rat_damage", L"images/enemy/Rat-damage.png", 0, 0, 66 * 2, 37 * 2, 2, 1, true);
	_loading->loadFrameImage(L"rat_death", L"images/enemy/Rat-death.png", 0, 0, 390 * 2, 34 * 2, 6, 1, true);


	_loading->loadFrameImage(L"egg_idle", L"images/enemy/Egg_idle.png", 0, 0, 96 * 2, 26 * 2, 2, 1, true);
	_loading->loadFrameImage(L"egg_damage", L"images/enemy/Egg_damage.png", 0, 0, 96 * 2, 26 * 2, 2, 1, true);
	_loading->loadImage(L"egg_death", L"images/enemy/Egg_death.png", 0, 0, 27 * 2, 26 * 2, true);

	//boss
	_loading->loadImage(L"1st_boss_bar", L"images/boss/1st_boss_bar.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 640 * 2, 14 * 2, false);
	_loading->loadImage(L"1st_boss_bullet", L"images/boss/1st_boss_bullet.png", WINSIZEX_NUM / 2, WINSIZEY_NUM / 2, 10 * 2, 14 * 2, true);
	_loading->loadFrameImage(L"1st_boss_idle", L"images/boss/1st_boss_idle.png", 0, 0, 1205 * 2, 182 * 2, 5, 1, true);
	_loading->loadFrameImage(L"1st_boss_attack", L"images/boss/1st_boss_attack.png", 0, 0, 1205 * 2, 182 * 2, 5, 1, true);
	_loading->loadFrameImage(L"1st_boss_die", L"images/boss/1st_boss_die.png", 0, 0, 1687 * 2, 182 * 2, 7, 1, true);
}