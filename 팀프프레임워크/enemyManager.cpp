#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{
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
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
	}


}

void enemyManager::render()
{
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}

}


//미니언 셋팅 함수
void enemyManager::setBaby()
{

	enemy* ebaby1;
	ebaby1 = new baby;
	ebaby1->init(1150, WINSIZEY / 2 + 58);
	_vMinion.push_back(ebaby1);

	enemy* ebaby2;
	ebaby2 = new baby;
	ebaby2->init(1920, WINSIZEY / 2 + 58);
	_vMinion.push_back(ebaby2);

	enemy* ebaby3;
	ebaby3 = new baby;
	ebaby3->init(4060, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby3);

	enemy* ebaby4;
	ebaby4 = new baby;
	ebaby4->init(6300, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby4);

	enemy* ebaby5;
	ebaby5 = new baby;
	ebaby5->init(7770, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby5);

	enemy* ebaby6;
	ebaby6 = new baby;
	ebaby6->init(9880, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby6);

	enemy* ebaby7;
	ebaby7 = new baby;
	ebaby7->init(10480, WINSIZEY / 2 + 625);
	_vMinion.push_back(ebaby7);


}
