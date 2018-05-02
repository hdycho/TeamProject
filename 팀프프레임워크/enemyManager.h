#pragma once
#include "gameNode.h"
#include "baby.h"
#include <vector>

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*>			 vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

private:
	vEnemy	_vMinion;
	viEnemy _viMinion;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//미니언 셋팅 함수
	void setBaby();
	
};

