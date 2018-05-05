#include "stdafx.h"
#include "Bomb.h"
#include "player.h"

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
	angle = 0;
	isCollision=false;
	return S_OK;
}

void Bomb::ObstacleUpdate()
{
	//여기서 플레이어랑 닿으면 터지게한다
	RECT temp;
	if (IntersectRect(&temp, &rc, &p->getKnightImage().rc))
	{
		EFFECTMANAGER->play("폭탄장애물폭발", GetCenterPos(rc).x, GetCenterPos(rc).y);
		angle = getAngle(GetCenterPos(rc).x, GetCenterPos(rc).y, GetCenterPos(p->getKnightImage().rc).x, GetCenterPos(p->getKnightImage().rc).y);
		
		p->getKnightImage().x += cosf(angle) * 35;
		p->getKnightImage().y += -sinf(angle) * 35;
		isCollision = true;
		isShow = false;

		//플레이어체력깎는다
	}
	
}
