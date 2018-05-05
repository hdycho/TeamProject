#include "stdafx.h"
#include "Iron.h"
#include "player.h"

Iron::Iron()
{
}


Iron::~Iron()
{
}

HRESULT Iron::init(int _x, int _y, string oName)
{
	Obstacle::init(_x, _y, oName);
	img = IMAGEMANAGER->findImage("¼èÀå¾Ö¹°");
	rc = RectMakeCenter(_x, _y, 50, 50);

	return S_OK;
}

void Iron::ObstacleUpdate()
{
	RECT temp;
	if (IntersectRect(&temp, &rc, &p->getKnightImage().rc))
	{
		float angle = getAngle(GetCenterPos(rc).x, GetCenterPos(rc).y, GetCenterPos(p->getKnightImage().rc).x, GetCenterPos(p->getKnightImage().rc).y);

		if (angle > 2 * PI)
		{
			angle -= 2 * PI;
		}

		if (angle > 0 && angle <= PI / 4)
		{
			p->getKnightImage().x = rc.right + 31;
		}
		if (angle > 7 * PI / 4 && angle < 2 * PI)
		{
			p->getKnightImage().x = rc.right + 31;
		}

		if (angle > PI / 3 && angle <= 2 * PI / 3)
		{
			p->getKnightImage().y = rc.top - 25;
			p->InitGravity();
		}

		if (angle > 3 * PI / 4 && angle <= 5 * PI / 4)
		{
			p->getKnightImage().x = rc.left - 31;
		}

		if (angle > 5 * PI / 4 && angle <= 7 * PI / 4)
		{
			p->getKnightImage().y = rc.bottom + 25;
		}
	}
}
