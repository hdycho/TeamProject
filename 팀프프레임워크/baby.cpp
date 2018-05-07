#include "stdafx.h"
#include "baby.h"
#include "player.h"

baby::baby()
{
}


baby::~baby()
{
}

HRESULT baby::init()
{
	return S_OK;
}

HRESULT baby::init(int x, int y)
{
	this->x = x;
	this->y = y;

	/*x = 1150;
	y = 360;*/

	enemy::init();

	IMAGEMANAGER->addFrameImage("baby", PathFile("image", "baby").c_str(), 257, 120, 5, 2, true, RGB(255, 0, 255));
	img = new image;
	img->init(PathFile("image", "baby").c_str(), 257, 120, 5, 2, true, RGB(255, 0, 255));

	epCol = new PixelCol;
	epCol->init(70, 20);
	epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);
	//currentFrameX = currentFrameY = 0;

	eState = LEFT_MOVE;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	int leftMove[] = { 0,1,2,3 };
	KEYANIMANAGER->addArrayFrameAnimation("babyLeftMove", "baby", leftMove, 4, 10, true);

	int rightMove[] = { 6,7,8,9 };
	KEYANIMANAGER->addArrayFrameAnimation("babyRightMove", "baby", rightMove, 4, 10, true);

	int leftDie[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("babyLeftDie", "baby", leftDie, 1, 7, true);

	int rightDie[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation("babyRightDie", "baby", rightDie, 1, 7, true);

	eMotion = new animation;
	*eMotion = *KEYANIMANAGER->findAnimation("babyLeftMove");
	eMotion->start();

	isRight = false;
	speed = 2.0f;
	getTime = 0;
	gravity = 1.0f;
	return S_OK;
}

//HRESULT baby::init(const char* imageName, POINT position)
//{
//	img = IMAGEMANAGER->addFrameImage("baby", "image/baby.bmp", 257, 120, 5, 2, true, RGB(255, 0, 255));
//	
//	currentFrameX = currentFrameY = 0;
//	
//	eState = LEFT_MOVE;
//
//	rc = RectMakeCenter(position.x, position.y, img->getFrameWidth(), img->getFrameHeight());
//
//	int leftMove[] = { 0,1,2,3 };
//	KEYANIMANAGER->addArrayFrameAnimation("babyLeftMove", "baby", leftMove, 4, 10, true);
//
//	int rightMove[] = { 6,7,8,9 };
//	KEYANIMANAGER->addArrayFrameAnimation("babyRightMove", "baby", rightMove, 4, 10, true);
//
//	int leftDie[] = { 4 };
//	KEYANIMANAGER->addArrayFrameAnimation("babyLeftDie", "baby", leftDie, 1, 7, true);
//
//	int rightDie[] = { 5 };
//	KEYANIMANAGER->addArrayFrameAnimation("babyRightDie", "baby", rightDie, 1, 7, true);
//
//	eMotion = KEYANIMANAGER->findAnimation("babyLeftMove");
//	eMotion->start();
//
//	isRight = false;
//	speed = 2.0f;
//	return S_OK;
//}


void baby::release()
{

}

void baby::update()
{
	px = GetCenterPos(_player->getKnightImage().rc).x;
	py = GetCenterPos(_player->getKnightImage().rc).y;

	if (getDistance(px, py, x, y) < 800)
	{
		enemy::update();
		//KEYANIMANAGER->update();
		move();
		rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
		enemyCollision();
		epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);
	}
}

void baby::render()
{
	if (getDistance(px, py, x, y) < 800)
	{
		draw();
		char temp[255];
		sprintf(temp, "%p", eMotion);
		TextOut(getMemDC(), x, y, temp, strlen(temp));
	}
}

void baby::move()
{
	x -= speed;
	getTime += TIMEMANAGER->getElapsedTime();

	if (getTime > 1.8f)
	{
		if (!isRight)
		{
			isRight = true;
			speed *= -1;
			getTime = 0;
			eState = RIGHT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("babyRightMove");
			eMotion->start();
		}
		else if (isRight)
		{
			isRight = false;
			speed *= -1;
			getTime = 0;
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("babyLeftMove");
			eMotion->start();
		}
	}
	eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());

}

void baby::draw()
{
	img->aniRender(getMemDC(), rc.left, rc.top, eMotion);
}

void baby::enemyCollision()
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
	if (epCol->RayCastingX(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 0, 0, 255, 0))
	{
		//speed = 0;
		if (!isRight)
		{
			isRight = true;
			getTime = 0;
			speed *= -1;
			eState = RIGHT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("babyRightMove");
			eMotion->start();
		}
		else if (isRight)
		{
			isRight = false;
			speed *= -1;
			getTime = 0;
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("babyLeftMove");
			eMotion->start();
		}
	}
}
