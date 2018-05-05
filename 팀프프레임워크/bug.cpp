#include "stdafx.h"
#include "bug.h"
#include "player.h"

bug::bug()
{
}


bug::~bug()
{
}

HRESULT bug::init()
{
	return S_OK;
}

HRESULT bug::init(int x, int y)
{
	this->x = x;
	this->y = y;

	enemy::init();

	epCol = new PixelCol;
	epCol->init(70, 20);

	IMAGEMANAGER->addFrameImage("bug", PathFile("image", "bug").c_str(), 300, 120, 4, 2, true, RGB(255, 0, 255));
	img = new image;
	img->init(PathFile("image", "bug").c_str(), 300, 120, 4, 2, true, RGB(255, 0, 255));

	eState = LEFT_MOVE;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	int leftMove[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("bugLeftMove", "bug", leftMove, 4, 10, true);

	int rightMove[] = { 4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("bugRightMove", "bug", rightMove, 4, 10, true);

	eMotion = new animation;
	*eMotion = *KEYANIMANAGER->findAnimation("bugLeftMove");
	eMotion->start();

	epCol = new PixelCol;
	epCol->init(70, 20);

	getTime = 0;
	speed = 2.5f;
	gravity = 1.0f;
	return S_OK;
}


//HRESULT bug::init(const char * imageName, POINT position)
//{
//	return S_OK;
//}

void bug::release()
{
}

void bug::update()
{
	enemy::update();
	//KEYANIMANAGER->update();
	move();
	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	enemyCollision();
	epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);
}

void bug::render()
{
	draw();
	char temp[255];
	sprintf(temp, "%p", eMotion);
	TextOut(getMemDC(), x, y, temp, strlen(temp));
}

void bug::move()
{
	int px, py;
	//_player->getKnightImage().rc;
	px = GetCenterPos(_player->getKnightImage().rc).x;
	py = GetCenterPos(_player->getKnightImage().rc).y;

	getTime += TIMEMANAGER->getElapsedTime();

	if (getDistance(px, py, x, y) < 500)
	{
		if (x < px)
		{
			x += speed;
			eState = RIGHT_MOVE;
			if (getTime > 1.0f)
			{
				getTime = 0;
				*eMotion = *KEYANIMANAGER->findAnimation("bugRightMove");
				eMotion->start();
			}

			if (y < py && fabs(py - y) > speed)
			{
				y += speed;
				if (getTime > 1.0f)
				{
					getTime = 0;
					*eMotion = *KEYANIMANAGER->findAnimation("bugRightMove");
					eMotion->start();
				}
			}
			else if (y > py && fabs(py - y) > speed)
			{
				y -= speed;
				if (getTime > 1.0f)
				{
					getTime = 0;
					*eMotion = *KEYANIMANAGER->findAnimation("bugRightMove");
					eMotion->start();
				}
			}
		}
		else if (x > px)
		{
			x -= speed;
			eState = LEFT_MOVE;
			if (getTime > 1.0f)
			{
				getTime = 0;
				*eMotion = *KEYANIMANAGER->findAnimation("bugLeftMove");
				eMotion->start();
			}

			if (y < py && fabs(py - y) > speed)
			{
				y += speed;
				if (getTime > 1.0f)
				{
					getTime = 0;
					*eMotion = *KEYANIMANAGER->findAnimation("bugLeftMove");
					eMotion->start();
				}
			}
			else if (y > py && fabs(py - y) > speed)
			{
				y -= speed;
				if (getTime > 1.0f)
				{
					getTime = 0;
					*eMotion = *KEYANIMANAGER->findAnimation("bugLeftMove");
					eMotion->start();
				}
			}
		}
	}
	eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());
}

void bug::draw()
{
	img->aniRender(getMemDC(), rc.left, rc.top, eMotion);
}

void bug::enemyCollision()
{
	//¹Ù´Ú
	if (epCol->RayCastingDownY(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 255, 0, 0))
	{
		epCol->setPosDownY(y);
		gravity = 0;
	}
	else
	{
		y += gravity;
		gravity = 1.0f;
	}

	//ÃµÀå
	if (epCol->RayCastingUpY(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 255, 0, 0))
	{
		epCol->setPosUpY(y);
	}

	//º®
	//if (epCol->RayCastingX(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 0, 0, 255, 0))
	//{
	//	speed = 0;
	//	y -= 10;
	//}
}