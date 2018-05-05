#include "stdafx.h"
#include "Wood.h"


Wood::Wood()
{
}


Wood::~Wood()
{
}

HRESULT Wood::init(int _x, int _y, string oName)
{
	Obstacle::init(_x, _y, oName);
	img = IMAGEMANAGER->findImage("나무장애물");
	rc = RectMakeCenter(_x, _y, 50, 50);

	return S_OK;
}

void Wood::ObstacleUpdate()
{

}
