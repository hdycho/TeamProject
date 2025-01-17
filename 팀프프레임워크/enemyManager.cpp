#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
	IMAGEMANAGER->addFrameImage("RB", PathFile("image", "rightBomb").c_str(), 80, 40, 2, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("RBomb", IMAGEMANAGER->findImage("RB"), 30, true, 20);
	IMAGEMANAGER->addFrameImage("LB", PathFile("image", "leftBomb").c_str(), 80, 40, 2, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("LBomb", IMAGEMANAGER->findImage("LB"), 30, true, 20);
	IMAGEMANAGER->addFrameImage("BE", PathFile("image", "boomerangEffect").c_str(), 448, 44, 8, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("BEffect", IMAGEMANAGER->findImage("BE"), 30, true, 5);
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{

	return S_OK;
}

void enemyManager::release()
{

}

void enemyManager::update()
{
	RECT updateRc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x, GetCenterPos(CAM->getCamRc()).y, 1600, 1200);
	for (int i = 0; i < _vMinion.size(); i++)
	{
		RECT temp;
		if (!IntersectRect(&temp, &updateRc, &_vMinion[i]->getRect()))continue;
		if (!_vMinion[i]->GetisEnemyDie())
			_vMinion[i]->update();
	}


}

void enemyManager::render()
{

	for (int i = 0; i < _vMinion.size(); i++)
	{
		RECT temp;
		if (!IntersectRect(&temp, &CAM->getCamRc(), &_vMinion[i]->getRect()))continue;
		if (!_vMinion[i]->GetisEnemyDie())
			_vMinion[i]->render();
	}

}


//미니언 셋팅 함수
void enemyManager::setMinion()
{
	//기본 에너미 11마리 셋팅
	enemy* ebaby1;
	ebaby1 = new baby;
	ebaby1->init(1150, 360);
	_vMinion.push_back(ebaby1);

	enemy* ebaby2;
	ebaby2 = new baby;
	ebaby2->init(1920, 360);
	_vMinion.push_back(ebaby2);

	enemy* ebaby3;
	ebaby3 = new baby;
	ebaby3->init(3080, 210);
	_vMinion.push_back(ebaby3);

	enemy* ebaby4;
	ebaby4 = new baby;
	ebaby4->init(4020, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby4);

	enemy* ebaby5;
	ebaby5 = new baby;
	ebaby5->init(4100, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby5);

	enemy* ebaby6;
	ebaby6 = new baby;
	ebaby6->init(6300, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby6);

	enemy* ebaby7;
	ebaby7 = new baby;
	ebaby7->init(7770, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby7);

	enemy* ebaby8;
	ebaby8 = new baby;
	ebaby8->init(9880, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby8);

	enemy* ebaby9;
	ebaby9 = new baby;
	ebaby9->init(10480, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby9);

	enemy* ebaby10;
	ebaby10 = new baby;
	ebaby10->init(10500, 500);
	_vMinion.push_back(ebaby10);

	enemy* ebaby11;
	ebaby11 = new baby;
	ebaby11->init(11350, 500);
	_vMinion.push_back(ebaby11);

	//플레이어를 따라오는 에너미 7마리 셋팅
	enemy* ebug1;
	ebug1 = new bug;
	ebug1->init(2100, 120);
	_vMinion.push_back(ebug1);

	enemy* ebug2;
	ebug2 = new bug;
	ebug2->init(3680, 700);
	_vMinion.push_back(ebug2);

	enemy* ebug3;
	ebug3 = new bug;
	ebug3->init(4640, 620);
	_vMinion.push_back(ebug3);

	enemy* ebug4;
	ebug4 = new bug;
	ebug4->init(5950, 640);
	_vMinion.push_back(ebug4);

	enemy* ebug5;
	ebug5 = new bug;
	ebug5->init(6650, 550);
	_vMinion.push_back(ebug5);

	enemy* ebug6;
	ebug6 = new bug;
	ebug6->init(8800, 670);
	_vMinion.push_back(ebug6);

	enemy* ebug7;
	ebug7 = new bug;
	ebug7->init(10850, 400);
	_vMinion.push_back(ebug7);

	//투척하는놈 9마리 셋팅
	enemy* eboomerang1;
	eboomerang1 = new boomerang;
	eboomerang1->init(2200, 360);
	_vMinion.push_back(eboomerang1);

	enemy* eboomerang2;
	eboomerang2 = new boomerang;
	eboomerang2->init(4520, 850);
	_vMinion.push_back(eboomerang2);

	enemy* eboomerang3;
	eboomerang3 = new boomerang;
	eboomerang3->init(5700, 850);
	_vMinion.push_back(eboomerang3);

	enemy* eboomerang4;
	eboomerang4 = new boomerang;
	eboomerang4->init(5950, 770);
	_vMinion.push_back(eboomerang4);

	enemy* eboomerang5;
	eboomerang5 = new boomerang;
	eboomerang5->init(8400, 850);
	_vMinion.push_back(eboomerang5);

	enemy* eboomerang6;
	eboomerang6 = new boomerang;
	eboomerang6->init(8000, 630);
	_vMinion.push_back(eboomerang6);

	enemy* eboomerang7;
	eboomerang7 = new boomerang;
	eboomerang7->init(8080, 410);
	_vMinion.push_back(eboomerang7);

	enemy* eboomerang8;
	eboomerang8 = new boomerang;
	eboomerang8->init(12150, 770);
	_vMinion.push_back(eboomerang8);

	enemy* eboomerang9;
	eboomerang9 = new boomerang;
	eboomerang9->init(12890, 420);
	_vMinion.push_back(eboomerang9);

	//봄버맨 셋팅
	enemy* ebomberman1;
	ebomberman1 = new bomberman;
	ebomberman1->init(1700, 330);
	_vMinion.push_back(ebomberman1);

	enemy* ebomberman2;
	ebomberman2 = new bomberman;
	ebomberman2->init(2820, 330);
	_vMinion.push_back(ebomberman2);

	enemy* ebomberman3;
	ebomberman3 = new bomberman;
	ebomberman3->init(4300, 850);
	_vMinion.push_back(ebomberman3);

	enemy* ebomberman4;
	ebomberman4 = new bomberman;
	ebomberman4->init(6260, 900);
	_vMinion.push_back(ebomberman4);

	enemy* ebomberman5;
	ebomberman5 = new bomberman;
	ebomberman5->init(7880, 900);
	_vMinion.push_back(ebomberman5);

	enemy* ebomberman6;
	ebomberman6 = new bomberman;
	ebomberman6->init(10720, 420);
	_vMinion.push_back(ebomberman6);

	enemy* ebomberman7;
	ebomberman7 = new bomberman;
	ebomberman7->init(11000, 420);
	_vMinion.push_back(ebomberman7);

	enemy* ebomberman8;
	ebomberman8 = new bomberman;
	ebomberman8->init(11660, 920);
	_vMinion.push_back(ebomberman8);

	enemy* ebomberman9;
	ebomberman9 = new bomberman;
	ebomberman9->init(12600, 490);
	_vMinion.push_back(ebomberman9);
}


