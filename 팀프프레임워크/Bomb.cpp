#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

HRESULT Bomb::init(int _x, int _y, string oName)
{
	Obstacle::init(_x, _y, oName);
	img = IMAGEMANAGER->findImage("폭탄장애물");
	rc = RectMakeCenter(_x, _y, 50, 50);

	return S_OK;
}

void Bomb::ObstacleUpdate()
{
	//여기서 플레이어랑 닿으면 터지게한다
}
