#include "stdafx.h"
#include "Boss.h"
//===========================//
void Boss::GetImageInit()
{
	//=======================//
	/*처음 시작 할 떄의 상태*/
	_bossState = L_MOVE;
	//=======================//
	/*기본이되는 이미지들*/
	IMAGEMANAGER->addFrameImage("BOSS", PathFile("image", "BOSS_RL_IDLE").c_str(), 1580, 552, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSSMOVE", PathFile("image", "BOSS_RL_MOVE").c_str(), 2844, 552, 18, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BOSS_GUN_ATK", PathFile("image", "BOSS_RL_ATK_GUN2").c_str(), 4000, 552, 17, 2, true, RGB(255, 0, 255));
	//=======================//
	/*보스 체력이 일정 이하일 떄의 기본 상태*/
	IMAGEMANAGER->addFrameImage("BOSSHURT", PathFile("image", "BOSS_RL_HURT_IDLE").c_str(), 1580, 552, 10, 2, true, RGB(255, 0, 255));

	int rHurt[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("RH", "BOSSHURT", rHurt, 10, 7, true);
	int lHurt[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("LH", "BOSSHURT", rHurt, 10, 7, true);
	//=======================//
	/*백대시*/
	IMAGEMANAGER->addFrameImage("BACK", PathFile("image", "BOSS_RL_BACK_DASH").c_str(), 2054, 552, 13, 2, true, RGB(255, 0, 255));

	int rBack[] = { 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("RBACK", "BACK", rBack, 13, 15, true);
	int lBack[] = { 0,   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12 };
	KEYANIMANAGER->addArrayFrameAnimation("LBACK", "BACK", lBack, 13, 15, true);
	//=======================//
	/*보스가 죽은 모습*/
	IMAGEMANAGER->addFrameImage("DEAD", PathFile("image", "BOSS_RL_DEAD").c_str(), 1264, 552, 8, 2, true, RGB(255, 0, 255));

	int rDead[] = { 0, 1, 2,  3,  4,  5,  6,  7 };
	KEYANIMANAGER->addArrayFrameAnimation("RDEAD", "DEAD", rDead, 8, 8, true);
	int lDead[] = { 8, 9, 10, 11, 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("LDEAD", "DEAD", lDead, 8, 8, true);
	//=======================//
	/*총쏘는 이미지 세팅하는것*/
	IMAGEMANAGER->addFrameImage("RIGHT_FIRE", PathFile("image", "R_GUN").c_str(), 640, 80, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("LEFT_FIRE", PathFile("image", "L_GUN").c_str(), 640, 80, 8, 1, true, RGB(255, 0, 255));

	BULLET->BulletSetting("RGF", IMAGEMANAGER->findImage("RIGHT_FIRE"), 5, true, 10);
	BULLET->BulletSetting("LGF", IMAGEMANAGER->findImage("LEFT_FIRE"), 5, true, 10);
	//=======================//				  																  
	/*칼질하는 이미지 세팅하는 것*/
	IMAGEMANAGER->addFrameImage("SWORD", PathFile("image", "BOSS_RL_ATK_SW").c_str(), 2100, 552, 7, 2, true, RGB(255, 0, 255));
	//=======================//				  
	/*보스 스킬 - 대포 쏘는 것, 특수 기술*/
	IMAGEMANAGER->addFrameImage("JUMP", PathFile("image", "BOSS_RL_JUMP").c_str(), 790, 552, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("STAY", PathFile("image", "BOSS_RL_JUMP_STAY").c_str(), 948, 552, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("FALL", PathFile("image", "BOSS_RL_JUMP_FALL").c_str(), 1738, 552, 11, 2, true, RGB(255, 0, 255));

	/*좌우 점프*/
	int rJump[] = { 0, 1, 2, 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("RJ", "JUMP", rJump, 5, 2, true);
	int lJump[] = { 5, 6, 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("LJ", "JUMP", lJump, 5, 2, true);
	/*좌우 유지*/
	int rStay[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("RJS", "STAY", rStay, 6, 20, true);
	int lStay[] = { 6, 7, 8, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("LJS", "STAY", lStay, 6, 20, true);
	/*떨어지는 이미지*/
	int rFall[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("RJF", "FALL", rFall, 11, 15, true);
	int lFall[] = { 11, 12, 13, 14, 15, 16 ,17, 18, 19, 20, 21 };
	KEYANIMANAGER->addArrayFrameAnimation("LJF", "FALL", lFall, 11, 15, true);

	/*폭탄 쏘는 것*/
	IMAGEMANAGER->addImage("BOOM", PathFile("image", "BOO").c_str(), 150, 150, true, RGB(255, 0, 255));

	BULLET->BulletSetting("CC", IMAGEMANAGER->findImage("BOOM"), 30, false, 0);
	BULLET->BulletSetting("CC1", IMAGEMANAGER->findImage("BOOM"), 30, false, 0);
	BULLET->BulletSetting("CC2", IMAGEMANAGER->findImage("BOOM"), 30, false, 0);
	BULLET->BulletSetting("CC3", IMAGEMANAGER->findImage("BOOM"), 30, false, 0);
	BULLET->BulletSetting("CC4", IMAGEMANAGER->findImage("BOOM"), 30, false, 0);
	//=======================//										          
	/*각 종 공격 이펙트*/
	/*칼질하는 이펙트*/
	EFFECTMANAGER->addEffect("우검기", PathFile("image", "RSWORD_EF").c_str(), 540, 100, 180, 100, 50, 1.0f, 3);
	EFFECTMANAGER->addEffect("좌검기", PathFile("image", "LSWORD_EF").c_str(), 540, 100, 180, 100, 50, 1.0f, 3);
	/*발포 이펙트*/
	EFFECTMANAGER->addEffect("총연", PathFile("image", "FIRE_EF").c_str(), 1400, 100, 100, 100, 10, 1.0f, 5);
	/*적중 이펙트*/
	EFFECTMANAGER->addEffect("총적중", PathFile("image", "FIRE_EF").c_str(), 1400, 100, 100, 100, 10, 1.0f, 5);
	/*대포 발포 이펙트*/
	EFFECTMANAGER->addEffect("폭연", PathFile("image", "BOMB_EF").c_str(), 4000, 250, 250, 250, 10, 1.0f, 5);
	/*대포 적중 이펙트*/
	EFFECTMANAGER->addEffect("폭적중", PathFile("image", "BOMB_EF").c_str(), 4000, 250, 250, 250, 10, 1.0f, 5);
	//=======================//
	/*좌우 기본 상태 이미지 초기화*/
	int rIdle[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9 };
	KEYANIMANAGER->addArrayFrameAnimation("R_IDLE", "BOSS", rIdle, 10, 2, true);
	int lIdle[] = { 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
	KEYANIMANAGER->addArrayFrameAnimation("L_IDLE", "BOSS", lIdle, 10, 2, true);
	//=======================//
	/*좌우 이동*/
	int rMove[] = { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("R_MOVE", "BOSSMOVE", rMove, 18, 10, true);
	int lMove[] = { 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("L_MOVE", "BOSSMOVE", lMove, 18, 10, true);
	//=======================//															    
	/*좌우 총쏘기*/
	int gunRightAtk[] = { 0,   1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16 };
	KEYANIMANAGER->addArrayFrameAnimation("RG", "BOSS_GUN_ATK", gunRightAtk, 17, 30, false);
	int gunLeftAtk[] = { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33 };
	KEYANIMANAGER->addArrayFrameAnimation("LG", "BOSS_GUN_ATK", gunLeftAtk, 17, 30, false);
	//=======================//
	/*근거리 공격 좌우*/
	int rAtk[] = { 0, 1, 2,  3,  4,  5,  6 };
	KEYANIMANAGER->addArrayFrameAnimation("RSA", "SWORD", rAtk, 7, 4, false);
	int lAtk[] = { 7, 8, 9, 10, 11, 12, 13 };
	KEYANIMANAGER->addArrayFrameAnimation("LSA", "SWORD", lAtk, 7, 4, false);
	//=======================//
	/*피통 40이하가 됐을 때 나타나는 초사이어인 기파.*/
	IMAGEMANAGER->addFrameImage("HURT", PathFile("image", "EF_2").c_str(), 540, 280, 3, 1, true, RGB(255, 0, 255));

	int hurt[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("H_EF", "HURT", hurt, 3, 8, true);
	//=======================//
	_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
	_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");
	_bossAni->start();
	//========================//





}
