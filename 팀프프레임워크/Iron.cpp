#include "stdafx.h"
#include "Iron.h"


Iron::Iron()
{
}


Iron::~Iron()
{
}

HRESULT Iron::init(int _x, int _y, string oName)
{
	Obstacle::init(_x, _y, oName);
	img = IMAGEMANAGER->findImage("ºË¿Âæ÷π∞");
	rc = RectMakeCenter(_x, _y, 50, 50);

	return S_OK;
}

void Iron::ObstacleUpdate()
{

}
