#include "stdafx.h"
#include "boomerang.h"
#include "player.h"

boomerang::boomerang()
{
}


boomerang::~boomerang()
{
}

HRESULT boomerang::init()
{
	return S_OK;
}

HRESULT boomerang::init(int x, int y)
{
	this->x = x;
	this->y = y;

	enemy::init();
	epCol = new PixelCol;
	epCol->init(70, 20);

	IMAGEMANAGER->addFrameImage("boomerang", PathFile("image", "boomerang").c_str(), 572, 120, 9, 2, true, RGB(255, 0, 255));
	img = new image;
	img->init(PathFile("image", "boomerang").c_str(), 572, 120, 9, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("BE", PathFile("image", "boomerangEffect").c_str(), 448, 44, 8, 1, true, RGB(255, 0, 255));
	Lweapon = new image;
	Lweapon->init(PathFile("image", "boomerangEffect").c_str(), 448, 44, 8, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("BEffect", IMAGEMANAGER->findImage("BE"), 30, true, 5);

	//EFFECTMANAGER->addEffect("boomerangEffect", PathFile("image", "boomerangEffect").c_str(), 224, 22, 28, 22, 60, 1, 30);

	eState = LEFT_MOVE;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	int leftMove[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftMove", "boomerang", leftMove, 1, 4, true);

	int rightMove[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightMove", "boomerang", rightMove, 1, 4, true);

	int leftOffence[] = { 15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftOffence", "boomerang", leftOffence, 6, 4, false);

	int rightOffence[] = { 2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightOffence", "boomerang", rightOffence, 6, 4, false);

	int leftDie[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftDie", "boomerang", leftDie, 1, 4, true);

	int rightDie[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightDie", "boomerang", rightDie, 1, 4, true);

	eMotion = new animation;
	*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftMove");
	eMotion->start();

	isRight = false;
	isOffence = false;
	speed = 0;
	getTime = 0;
	getDelayTime = 0;
	gravity = 1.0f;

	BULLET->UseCollision("BEffect", 28, 22); //¹ÝÁö¸§°ª ³Ö¾îÁà¾ßÇÔ
	return S_OK;
}

HRESULT boomerang::init(const char* imageName, POINT position)
{
	return S_OK;
}

void boomerang::release()
{

}

void boomerang::update()
{
	//static int bx = 0, by = 0;
	//BULLET->IsCollision("BEffect", &bx, &by, true, IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), RectMake(0, 0, 0, 0));
	//
	//int px, py;
	//px = GetCenterPos(_player->getKnightImage().rc).x;
	//py = GetCenterPos(_player->getKnightImage().rc).y;
	//eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());
	//
	//rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());
	//
	//getTime += TIMEMANAGER->getElapsedTime();
	//getDelayTime += TIMEMANAGER->getElapsedTime();
	//
	//if (getDelayTime > 1.8f)
	//{
	//	if (px < x)
	//	{
	//		isRight = false;
	//		eState = LEFT_MOVE;
	//		*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftMove");
	//		eMotion->start();
	//
	//		if (getDistance(px, py, x, y) < 200 && !isRight)
	//		{
	//			eState = LEFT_OFFENCE;
	//			*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftOffence");
	//			eMotion->start();
	//			isOffence = true;
	//			getTime = getDelayTime;
	//			getDelayTime = 0;
	//		
	//			if (getTime > 2.8f)
	//			{
	//				BULLET->Shot("BEffect", x, y, PI, 0, 5);
	//				getTime = 0;
	//			}
	//			
	//		}
	//		
	//	}
	//	else if (px > x)
	//	{
	//		isRight = true;
	//		eState = RIGHT_MOVE;
	//		*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightMove");
	//		eMotion->start();
	//
	//		if (getDistance(px, py, x, y) < 200 && isRight)
	//		{
	//			eState = RIGHT_OFFENCE;
	//			*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightOffence");
	//			eMotion->start();
	//			isOffence = true;
	//			getTime = getDelayTime;
	//			getDelayTime = 0;
	//			
	//			if (getTime > 2.8f)
	//			{
	//				BULLET->Shot("BEffect", x, y, PI * 2, 0, 15);
	//				getTime = 0;
	//			}
	//		}
	//	}
	//}
	enemy::update();

	int px, py;
	px = GetCenterPos(_player->getKnightImage().rc).x;
	py = GetCenterPos(_player->getKnightImage().rc).y;
	eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	static int bx = 0, by = 0;
	BULLET->IsCollision("BEffect", &bx, &by, true, IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), RectMake(0, 0, 0, 0));


	getDelayTime += TIMEMANAGER->getElapsedTime();

	if (getDelayTime > 1.5f)
	{
		if (getDistance(px, py, x, y) < 200 && !isRight)
		{

			isOffence = true;
			getDelayTime = 0;
			if (px < x)
			{
				if (!eMotion->isPlay())
					BULLET->Shot("BEffect", x, y, PI, 0, 10);
				eState = LEFT_OFFENCE;
				*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftOffence");
				eMotion->start();

			}
			else if (px > x)
			{
				if (!eMotion->isPlay())
					BULLET->Shot("BEffect", x, y, PI * 2, 0, 10);
				eState = RIGHT_OFFENCE;
				*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightOffence");
				eMotion->start();

			}

		}
		else if (getDistance(px, py, x, y) > 200)
		{
			isOffence = false;
			move();
		}

		if (getDistance(px, py, x, y) < 200 && isRight)
		{
			isOffence = true;
			getDelayTime = 0;
			if (px < x)
			{
				if (!eMotion->isPlay())
					BULLET->Shot("BEffect", x, y, PI, 0, 10);
				eState = LEFT_OFFENCE;
				*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftOffence");
				eMotion->start();

			}
			else if (px > x)
			{
				if (!eMotion->isPlay())
					BULLET->Shot("BEffect", x, y, PI * 2, 0, 10);
				eState = RIGHT_OFFENCE;
				*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightOffence");
				eMotion->start();

			}


		}
		else if (getDistance(px, py, x, y) > 200)
		{
			isOffence = false;
			move();
		}
	}

	enemyCollision();
	epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);

}

void boomerang::render()
{
	draw();
}

void boomerang::move()
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
			*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightMove");
			eMotion->start();
		}
		else if (isRight)
		{
			isRight = false;
			speed *= -1;
			getTime = 0;
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftMove");
			eMotion->start();
		}
	}

}

void boomerang::draw()
{
	img->aniRender(getMemDC(), rc.left, rc.top, eMotion);
	Lweapon->aniRender(getMemDC(), rc.left, rc.top, eMotion);
}

void boomerang::enemyCollision()
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
	//}
}