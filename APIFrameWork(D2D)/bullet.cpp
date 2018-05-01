#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
}

bullet::~bullet()
{
}

HRESULT bullet::init(void)
{
	frameX = count = 0;
	return S_OK;
}

void bullet::release(void)
{
	vGunBullet.clear();
	vShotGunBullet.clear();
	vRocketBullet.clear();
	vPlasmaBullet.clear();
	somethings.clear();
	isAttacks.clear();
	isDelets.clear();
}

void bullet::update(void)
{
	collisionBullet();
	pleaseDelete();
	moveBullet();
	if (dogWeaponInfo->currentWeapon != EWEAPON_NONE && dogWeaponInfo->currentWeapon != EWEAPON_CLUP) {
		if (KEYMANAGER->isOnceKeyDown(_mGameKey.ATTACK)) {
			createBullet();
		}
	}
}

void bullet::render(void)
{
	for (int i = 0; i < vRocketBullet.size(); ++i) {
		Rt->SetTransform(D2D1::Matrix3x2F::Rotation(vRocketBullet.at(i).angle, { CAMERAMANAGER->getAbsPosition(vRocketBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vRocketBullet.at(i).position).y }));
		IMAGEMANAGER->frameRender(L"rocket_bullet", Rt, frameX % 3, 3 - dogWeaponInfo->aWeapon[4].upgrade / 5, CAMERAMANAGER->getAbsPosition(vRocketBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vRocketBullet.at(i).position).y);
		Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	for (int i = 0; i < vShotGunBullet.size(); ++i) {
		Rt->SetTransform(D2D1::Matrix3x2F::Rotation(-vShotGunBullet.at(i).angle, { CAMERAMANAGER->getAbsPosition(vShotGunBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vShotGunBullet.at(i).position).y }));
		IMAGEMANAGER->frameRender(L"shotgun_bullet", Rt, frameX % 4, 3 - dogWeaponInfo->aWeapon[3].upgrade / 5, CAMERAMANAGER->getAbsPosition(vShotGunBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vShotGunBullet.at(i).position).y);
		Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	for (int i = 0; i < vGunBullet.size(); ++i) {
		Rt->SetTransform(D2D1::Matrix3x2F::Rotation(vGunBullet.at(i).angle, { CAMERAMANAGER->getAbsPosition(vGunBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vGunBullet.at(i).position).y }));
		IMAGEMANAGER->frameRender(L"gun_bullet", Rt, frameX % 3, 3 - dogWeaponInfo->aWeapon[2].upgrade / 5, CAMERAMANAGER->getAbsPosition(vGunBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vGunBullet.at(i).position).y);
		Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	for (int i = 0; i < vPlasmaBullet.size(); ++i) {
		Rt->SetTransform(D2D1::Matrix3x2F::Rotation(vPlasmaBullet.at(i).angle, { CAMERAMANAGER->getAbsPosition(vPlasmaBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vPlasmaBullet.at(i).position).y }));
		IMAGEMANAGER->frameRender(L"plasma_bullet", Rt, frameX % 3, 3 - dogWeaponInfo->aWeapon[5].upgrade / 5, CAMERAMANAGER->getAbsPosition(vPlasmaBullet.at(i).position).x, CAMERAMANAGER->getAbsPosition(vPlasmaBullet.at(i).position).y);
		Rt->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}

void bullet::collisionBullet()
{
	if (&clubRect->left != 0 && &clubRect->top != 0 && &clubRect->right != 0 && &clubRect->bottom != 0) {
		int a = 0;
		for (int i = 0; i < somethings.size(); ++i) {
			D2D_RECT_F tmpRect = *clubRect;
			if (CheckCollisionRects(tmpRect, *somethings.at(i)) && !*isAttacks.at(i)) {
				clubRect->left = 0;
				clubRect->top = 0;
				clubRect->right = 0;
				clubRect->bottom = 0;
				SOUNDMANAGER->play("hit_club", 1.0f * effectSound);
				*isAttacks.at(i) = true;
				*vAtkNum.at(i) = (int)(dogWeaponInfo->aWeapon[1].upgrade / 5) + 1;
				break;
			}
		}
	}

	//gun
	for (int j = 0; j < vGunBullet.size(); ++j) {
		bool breaking = false;
		for (int i = 0; i < somethings.size(); ++i) {
			if (CheckCollisionRects({ vGunBullet.at(j).position.x - 27, vGunBullet.at(j).position.y - 11 , vGunBullet.at(j).position.x + 27, vGunBullet.at(j).position.y + 11 }, *somethings.at(i))) {
				*isAttacks.at(i) = true;
				SOUNDMANAGER->play("hit_bullet", 1.0f * effectSound);
				*vAtkNum.at(i) = (int)(dogWeaponInfo->aWeapon[2].upgrade / 5) + 1;
				EFFECTMANAGER->play(L"gun_destroy", vGunBullet.at(j).position.x, vGunBullet.at(j).position.y);
				vector<SBULLET>::iterator vIter = vGunBullet.begin();
				vIter += j;
				vGunBullet.erase(vIter);
				breaking = true;
				break;
			}
		}
		if (breaking) break;
	}
	//shotgun
	for (int j= 0;j < vShotGunBullet.size(); ++j) {
		bool breaking = false;
		for (int i = 0; i < somethings.size(); ++i) {
			if (CheckCollisionRects({ vShotGunBullet.at(j).position.x - 27, vShotGunBullet.at(j).position.y - 5 , vShotGunBullet.at(j).position.x + 27, vShotGunBullet.at(j).position.y + 5 }, *somethings.at(i))) {
				*isAttacks.at(i) = true;
				SOUNDMANAGER->play("hit_bullet", 0.3f * effectSound);
				*vAtkNum.at(i) = (int)(dogWeaponInfo->aWeapon[3].upgrade / 5) + 1;
				EFFECTMANAGER->play(L"shotgun_destroy", vShotGunBullet.at(j).position.x, vShotGunBullet.at(j).position.y);
				vector<SBULLET>::iterator vIter = vShotGunBullet.begin();
				vIter += j;
				vShotGunBullet.erase(vIter);
				breaking = true;
				break;
			}
		}
		if (breaking) break;
	}
	//rocket
	for (int j = 0; j < vRocketBullet.size(); ++j) {
		bool breaking = false;
		for (int i = 0; i < somethings.size(); ++i) {
			if (CheckCollisionRects({ vRocketBullet.at(j).position.x - 44, vRocketBullet.at(j).position.y - 9 , vRocketBullet.at(j).position.x + 44, vRocketBullet.at(j).position.y + 9 }, *somethings.at(i))) {
				for (int k = 0; k < somethings.size(); ++k) {
					if (i == k) continue;
					else {
						if (CheckCollisionRects(*somethings.at(i), *somethings.at(k))) {
							*isAttacks.at(k) = true;
							SOUNDMANAGER->play("hit_bullet", 1.0f * effectSound);
							*vAtkNum.at(k) = (int)(dogWeaponInfo->aWeapon[4].upgrade / 5) + 1;
						}
					}
				}

				CAMERAMANAGER->setVibeMode();
				SOUNDMANAGER->play("hit_bullet", 1.0f * effectSound);
				SOUNDMANAGER->play("bumb", 1.0f * effectSound);
				*isAttacks.at(i) = true;
				*vAtkNum.at(i) = (int)(dogWeaponInfo->aWeapon[4].upgrade / 5) + 1;
				EFFECTMANAGER->play(L"rocket_destroy", vRocketBullet.at(j).position.x, vRocketBullet.at(j).position.y);
				vector<SBULLET>::iterator vIter = vRocketBullet.begin();
				vIter += j;
				vRocketBullet.erase(vIter);
				breaking = true;
				break;
			}
		}
		if (breaking) break;
	}
	//plasma
	for (int j = 0; j < vPlasmaBullet.size(); ++j) {
		bool breaking = false;
		for (int i = 0; i < somethings.size(); ++i) {
			if (CheckCollisionRects({ vPlasmaBullet.at(j).position.x - 8, vPlasmaBullet.at(j).position.y - 8 , vPlasmaBullet.at(j).position.x + 8, vPlasmaBullet.at(j).position.y + 8 }, *somethings.at(i))) {
				*isAttacks.at(i) = true;
				SOUNDMANAGER->play("hit_bullet", 1.0f * effectSound);
				*vAtkNum.at(i) = (int)(dogWeaponInfo->aWeapon[5].upgrade / 5) + 1;
				EFFECTMANAGER->play(L"plasma_destroy", vPlasmaBullet.at(j).position.x, vPlasmaBullet.at(j).position.y);
				vector<SBULLET>::iterator vIter = vPlasmaBullet.begin();
				vIter += j;
				vPlasmaBullet.erase(vIter);
				breaking = true;
				break;
			}
		}
		if (breaking) break;
	}
}

void bullet::pleaseDelete()
{
	for (int i = 0; i < isDelets.size(); ++i) {
		if (*isDelets.at(i) == true) {
			deleteSomeThings(somethings.at(i), isAttacks.at(i), isDelets.at(i), vAtkNum.at(i));
			break;
		}
	}
}

void bullet::createBullet()
{
	switch (dogWeaponInfo->currentWeapon)
	{
	case EWEAPON_GUN:
		//27,11 width/2, height/2
		if (dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum > 0) {
			dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum--;
			SOUNDMANAGER->play("Blaster", 1.0f * effectSound);
			switch (dogInfo->getView())
			{
			case EViEWDIRECTION_LEFT:
				vGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 29.5f }, 180.0f, TIMEMANAGER->getWorldTime() + 0.7f });
				EFFECTMANAGER->play(L"gun_flash_left", vGunBullet.back().position.x, vGunBullet.back().position.y);
				break;
			case EViEWDIRECTION_RIGHT:
				vGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y - 30.5f }, 0.0f , TIMEMANAGER->getWorldTime() + 0.7f });
				EFFECTMANAGER->play(L"gun_flash", vGunBullet.back().position.x, vGunBullet.back().position.y);
				break;
			case EViEWDIRECTION_UP:
				vGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 270.0f, TIMEMANAGER->getWorldTime() + 0.7f });
				EFFECTMANAGER->play(L"gun_flash_up", vGunBullet.back().position.x, vGunBullet.back().position.y);
				break;
			case EViEWDIRECTION_DOWN:
				if (dogInfo->getIsAir()) {
					vGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 90.0f, TIMEMANAGER->getWorldTime() + 0.7f });
					EFFECTMANAGER->play(L"gun_flash_down", vGunBullet.back().position.x, vGunBullet.back().position.y);
				}
				break;
			}
		}
		break;
	case EWEAPON_SHOTGUN:
		if (dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum > 0) {
		dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum--;
		SOUNDMANAGER->play("gun", 1.0f * effectSound);
		switch (dogInfo->getView())
		{
		case EViEWDIRECTION_LEFT:
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 180.0f, TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 177.0f, TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 178.5f, TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 181.5f, TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 183.0f, TIMEMANAGER->getWorldTime() + 2.5f });
			EFFECTMANAGER->play(L"shotgun_flash_left", vShotGunBullet.back().position.x, vShotGunBullet.back().position.y);
			break;
		case EViEWDIRECTION_RIGHT:
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y -24.5f }, 0.0f , TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y -24.5f }, 359.0f , TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y -24.5f }, 358.0f , TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y -24.5f }, 1.0f , TIMEMANAGER->getWorldTime() + 2.5f });
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y -24.5f }, 2.0f , TIMEMANAGER->getWorldTime() + 2.5f });
			EFFECTMANAGER->play(L"shotgun_flash", vShotGunBullet.back().position.x, vShotGunBullet.back().position.y);
			break;
		case EViEWDIRECTION_UP:
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 90.0f, TIMEMANAGER->getWorldTime() +2.5f});
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 91.0f, TIMEMANAGER->getWorldTime() +2.5f});
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 92.0f, TIMEMANAGER->getWorldTime() +2.5f});
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 88.0f, TIMEMANAGER->getWorldTime() +2.5f});
			vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 89.0f, TIMEMANAGER->getWorldTime() +2.5f});
			EFFECTMANAGER->play(L"shotgun_flash_up", vShotGunBullet.back().position.x, vShotGunBullet.back().position.y);
			break;
		case EViEWDIRECTION_DOWN:
			if (dogInfo->getIsAir()) {
				vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 270.0f, TIMEMANAGER->getWorldTime() + 2.5f });
				vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 268.0f, TIMEMANAGER->getWorldTime() + 2.5f });
				vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 269.0f, TIMEMANAGER->getWorldTime() + 2.5f });
				vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 271.0f, TIMEMANAGER->getWorldTime() + 2.5f });
				vShotGunBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 272.0f, TIMEMANAGER->getWorldTime() + 2.5f });
				EFFECTMANAGER->play(L"shotgun_flash_down", vShotGunBullet.back().position.x, vShotGunBullet.back().position.y);
			}
			break;
		}
		}
		break;
	case EWEAPON_ROCKET:
		if (dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum > 0) {
			dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum--;
			SOUNDMANAGER->play("Rocket", 0.5f * effectSound);
			switch (dogInfo->getView())
			{
			case EViEWDIRECTION_LEFT:
				dogInfo->modifyX(2.0f);
				vRocketBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 24.5f }, 180.0f, TIMEMANAGER->getWorldTime() + 2.5f, 0.0f });
				EFFECTMANAGER->play(L"rocket_flash_left", vRocketBullet.back().position.x, vRocketBullet.back().position.y);
				break;
			case EViEWDIRECTION_RIGHT:
				dogInfo->modifyX(-2.0f);
				vRocketBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y - 24.5f }, 0.0f , TIMEMANAGER->getWorldTime() + 2.5f , 0.0f });
				EFFECTMANAGER->play(L"rocket_flash", vRocketBullet.back().position.x, vRocketBullet.back().position.y);
				break;
			case EViEWDIRECTION_UP:
				vRocketBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 270.0f , TIMEMANAGER->getWorldTime() + 2.5f , 0.0f });
				EFFECTMANAGER->play(L"rocket_flash_up", vRocketBullet.back().position.x, vRocketBullet.back().position.y);
				break;
			case EViEWDIRECTION_DOWN:
				dogInfo->modifyY(2.0f);
				if (dogInfo->getIsAir()) {
					vRocketBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 90.0f, TIMEMANAGER->getWorldTime() + 2.5f, 0.0f });
					EFFECTMANAGER->play(L"rocket_flash_down", vRocketBullet.back().position.x, vRocketBullet.back().position.y);
				}
				break;
			}
		}
		break;
	case EWEAPON_PLASMA:
		if (dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum > 0) {
			dogWeaponInfo->aWeapon[dogWeaponInfo->currentWeapon].bulletNum--;
			SOUNDMANAGER->play("plasmagun", 1.0f * effectSound);
			switch (dogInfo->getView())
			{
			case EViEWDIRECTION_LEFT:
				vPlasmaBullet.push_back({ { dogInfo->getPoint()->x - 34, dogInfo->getPoint()->y - 23.5f }, 180.0f, TIMEMANAGER->getWorldTime() + 2.0f , 0.0f ,9.0f});
				EFFECTMANAGER->play(L"plasma_flash_left", vPlasmaBullet.back().position.x, vPlasmaBullet.back().position.y);
				break;
			case EViEWDIRECTION_RIGHT:
				vPlasmaBullet.push_back({ { dogInfo->getPoint()->x + 34, dogInfo->getPoint()->y - 23.5f }, 0.0f , TIMEMANAGER->getWorldTime() + 2.0f, 0.0f,9.0f });
				EFFECTMANAGER->play(L"plasma_flash", vPlasmaBullet.back().position.x, vPlasmaBullet.back().position.y);
				break;
			case EViEWDIRECTION_UP:
				vPlasmaBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 65 }, 90.0f, TIMEMANAGER->getWorldTime() + 2.0f , 0.0f, 9.0f });
				EFFECTMANAGER->play(L"plasma_flash_up", vPlasmaBullet.back().position.x, vPlasmaBullet.back().position.y);
				break;
			case EViEWDIRECTION_DOWN:
				if (dogInfo->getIsAir()) {
					vPlasmaBullet.push_back({ { dogInfo->getPoint()->x, dogInfo->getPoint()->y - 32 }, 270.0f, TIMEMANAGER->getWorldTime() + 2.0f , 0.0f ,9.0f });
					EFFECTMANAGER->play(L"plasma_flash_down", vPlasmaBullet.back().position.x, vPlasmaBullet.back().position.y);
				}
				break;
			}
		}
		break;
	}
}

void bullet::moveBullet()
{
	//이미지 프레임
	count++;
	if (count % 3 == 0) {
		frameX++;
		if (frameX == 12) {
			frameX = 0;
		}
	}

	//gun
	for (int i = 0; i < vGunBullet.size(); ++i) {
		vGunBullet.at(i).position.x += cosf(vGunBullet.at(i).angle *(PI / 180))*12.0f;
		vGunBullet.at(i).position.y += sinf(vGunBullet.at(i).angle *(PI / 180))*12.0f;
		if (dogInfo->checkUserCollision({ vGunBullet.at(i).position.x - 12.0f, vGunBullet.at(i).position.y - 12.0f , vGunBullet.at(i).position.x + 12.0f, vGunBullet.at(i).position.y + 12.0f }) != 0.0f) {

			EFFECTMANAGER->play(L"gun_destroy", vGunBullet.at(i).position.x, vGunBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vGunBullet.begin();
			vIter += i;
			vGunBullet.erase(vIter);
			break;
		}
		if (TIMEMANAGER->getWorldTime() >= vGunBullet.at(i).time) {
			EFFECTMANAGER->play(L"gun_destroy", vGunBullet.at(i).position.x, vGunBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vGunBullet.begin();
			vIter += i;
			vGunBullet.erase(vIter);
			break;
		}
	}
	//shotgun
	for (int i = 0; i < vShotGunBullet.size(); ++i) {
		vShotGunBullet.at(i).position.x += cosf(vShotGunBullet.at(i).angle *(PI / 180))*10.0f;
		vShotGunBullet.at(i).position.y -= sinf(vShotGunBullet.at(i).angle *(PI / 180))*10.0f;
		float angle = dogInfo->checkUserCollision({ vShotGunBullet.at(i).position.x - 5, vShotGunBullet.at(i).position.y - 5 , vShotGunBullet.at(i).position.x + 5, vShotGunBullet.at(i).position.y + 5 });
		if (angle != 0.0f) {
			while (angle >= 180) {
				angle -= 180.0f;
			}
			vShotGunBullet.at(i).angle = 2 * angle - vShotGunBullet.at(i).angle;
			if (vShotGunBullet.at(i).angle >= 360.0f) {
				vShotGunBullet.at(i).angle -= 360.0f;
			}
			while (dogInfo->checkUserCollision({ vShotGunBullet.at(i).position.x - 5, vShotGunBullet.at(i).position.y - 5 , vShotGunBullet.at(i).position.x + 5, vShotGunBullet.at(i).position.y + 5 })==0.0f) {
				vShotGunBullet.at(i).position.x +=  cosf(vShotGunBullet.at(i).angle *(PI / 180))*10.0f;
				vShotGunBullet.at(i).position.y -=  sinf(vShotGunBullet.at(i).angle *(PI / 180))*10.0f;
			}
		}
		if (TIMEMANAGER->getWorldTime() >= vShotGunBullet.at(i).time) {
			EFFECTMANAGER->play(L"shotgun_destroy", vShotGunBullet.at(i).position.x, vShotGunBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vShotGunBullet.begin();
			vIter += i;
			vShotGunBullet.erase(vIter);
			break;
		}
	}
	//rocket
	for (int i = 0; i < vRocketBullet.size(); ++i) {
		vRocketBullet.at(i).gravity += 0.5f;
		if (vRocketBullet.at(i).gravity >= 12.0f) vRocketBullet.at(i).gravity = 12.0f;
		vRocketBullet.at(i).position.x += cosf(vRocketBullet.at(i).angle *(PI / 180))*vRocketBullet.at(i).gravity;
		vRocketBullet.at(i).position.y += sinf(vRocketBullet.at(i).angle *(PI / 180))*vRocketBullet.at(i).gravity;
		if (dogInfo->checkUserCollision({ vRocketBullet.at(i).position.x - 12.0f, vRocketBullet.at(i).position.y - 12.0f , vRocketBullet.at(i).position.x + 12.0f, vRocketBullet.at(i).position.y + 12.0f }) != 0.0f) {

			CAMERAMANAGER->setVibeMode();
			SOUNDMANAGER->play("bumb", 1.0f * effectSound);
			EFFECTMANAGER->play(L"rocket_destroy", vRocketBullet.at(i).position.x, vRocketBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vRocketBullet.begin();
			vIter += i;
			vRocketBullet.erase(vIter);
			break;
		}
		if (TIMEMANAGER->getWorldTime() >= vRocketBullet.at(i).time) {

			CAMERAMANAGER->setVibeMode();
			SOUNDMANAGER->play("bumb", 1.0f * effectSound);
			EFFECTMANAGER->play(L"rocket_destroy", vRocketBullet.at(i).position.x, vRocketBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vRocketBullet.begin();
			vIter += i;
			vRocketBullet.erase(vIter);
			break;
		}
	}
	//plasma
	for (int i = 0; i < vPlasmaBullet.size(); ++i) {
		vPlasmaBullet.at(i).position.x += cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * vPlasmaBullet.at(i).speedx;
		vPlasmaBullet.at(i).position.y -= sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * vPlasmaBullet.at(i).speedx;;
		vPlasmaBullet.at(i).position.y += vPlasmaBullet.at(i).gravity;
		vPlasmaBullet.at(i).gravity += 0.2f;
		float angle = dogInfo->checkUserCollision({ vPlasmaBullet.at(i).position.x - 11, vPlasmaBullet.at(i).position.y -11 , vPlasmaBullet.at(i).position.x + 11, vPlasmaBullet.at(i).position.y + 11 });
		if (angle != 0.0f) {
			while (angle >= 180) {
				angle -= 180.0f;
			}
			vPlasmaBullet.at(i).speedx -= vPlasmaBullet.at(i).speedx * 0.02f;
			float tmpAngle;
			if ((sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) >= 0 && (cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f) >= 0) {
				tmpAngle = atanf((sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) / (cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f))* (180 / PI);
			}
			else if((sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) >= 0 && (cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f) < 0) {
				tmpAngle = 180.0f - atanf(fabsf(sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) / fabsf(cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f))* (180 / PI);
			}
			else if ((sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) < 0 && (cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f) < 0) {
				tmpAngle = 180.0f + atanf(fabsf(sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) / fabsf(cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f))* (180 / PI);
			}
			else if ((sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) < 0 && (cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f) >= 0) {
				tmpAngle = 360.0f - atanf(fabsf(sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f - vPlasmaBullet.at(i).gravity) / fabsf(cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f))* (180 / PI);
			}
			vPlasmaBullet.at(i).gravity = 0;
			vPlasmaBullet.at(i).angle = 2 * angle - tmpAngle;
			if (vPlasmaBullet.at(i).angle >= 360.0f) {
				vPlasmaBullet.at(i).angle -= 360.0f;
			}
			while (dogInfo->checkUserCollision({ vPlasmaBullet.at(i).position.x - 11, vPlasmaBullet.at(i).position.y - 11 , vPlasmaBullet.at(i).position.x + 11, vPlasmaBullet.at(i).position.y + 11 }) == 0.0f) {
				vPlasmaBullet.at(i).position.x += cosf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f;
				vPlasmaBullet.at(i).position.y -= sinf(vPlasmaBullet.at(i).angle *(PI / 180)) * 10.0f;
			}
		}

		if (TIMEMANAGER->getWorldTime() >= vPlasmaBullet.at(i).time) {
			EFFECTMANAGER->play(L"plasma_destroy", vPlasmaBullet.at(i).position.x, vPlasmaBullet.at(i).position.y);
			vector<SBULLET>::iterator vIter = vPlasmaBullet.begin();
			vIter += i;
			vPlasmaBullet.erase(vIter);
			break;
		}
	}
}