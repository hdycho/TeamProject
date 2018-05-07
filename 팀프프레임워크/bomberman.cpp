#include "stdafx.h"
#include "bomberman.h"
#include "player.h"

bomberman::bomberman()
{
}


bomberman::~bomberman()
{
}

HRESULT bomberman::init()
{
	return S_OK;
}

HRESULT bomberman::init(int x, int y)
{
	this->x = x;
	this->y = y;

	epCol = new PixelCol;
	epCol->init(10, 10);
	epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);

	enemy::init();

	IMAGEMANAGER->addFrameImage("bomberman", PathFile("image", "bomberman").c_str(), 1235, 150, 13, 2, true, RGB(255, 0, 255));
	img = new image;
	img->init(PathFile("image", "bomberman").c_str(), 1235, 150, 13, 2, true, RGB(255, 0, 255));

	EFFECTMANAGER->addEffect("bombEffect", PathFile("image", "bombEffect").c_str(), 560, 112, 112, 112, 10, 1, 30);

	eState = LEFT_MOVE;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	int leftMove[] = { 24, 25 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanLeftMove", "bomberman", leftMove, 2, 6, true);

	int rightMove[] = { 0,1 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanRightMove", "bomberman", rightMove, 2, 6, true);

	int leftOffence[] = { 23,22,21,20,19,18,17,16,15 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanLeftOffence", "bomberman", leftOffence, 9, 9, false);

	int rightOffence[] = { 2,3,4,5,6,7,8,9,10 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanRightOffence", "bomberman", rightOffence, 9, 9, false);

	int leftDie[] = { 12 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanLeftDie", "bomberman", leftDie, 1, 4, true);

	int rightDie[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("bombermanRightDie", "bomberman", rightDie, 1, 4, true);

	eMotion = new animation;
	*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftMove");
	eMotion->start();

	isRight = false;
	isOffence = false;
	isEnemyBulletFire = false;
	isCollision = false;
	speed = 1.0f;
	getTime = 0;
	getDelayTime = 0;
	gravity = 1.0f;
	cnt = 0;
	moveCnt = 1;

	BULLET->UseCollision("LBomb", 20, 20);
	BULLET->UseCollision("RBomb", 20, 20);
	return S_OK;
}

HRESULT bomberman::init(const char* imageName, POINT position)
{
	return S_OK;
}

void bomberman::release()
{

}

void bomberman::update()
{
	px = GetCenterPos(_player->getKnightImage().rc).x;
	py = GetCenterPos(_player->getKnightImage().rc).y;



	if (getDistance(px, py, x, y) < 800)
	{
		if (moveCnt == 1)
		{
			move();
			moveCnt = 0;
		}

		if (isEnemyBulletFire && !eMotion->isPlay())
		{
			if (eState == LEFT_OFFENCE)
			{
				BULLET->Shot("LBomb", x, y, PI / 3 * 2, 1.0f, 14);
				isEnemyBulletFire = false;
			}
			else if (eState == RIGHT_OFFENCE)
			{
				BULLET->Shot("RBomb", x, y, PI / 3, 1.0f, 14);
				isEnemyBulletFire = false;
			}
		}

		enemy::update();
		static int exX = 0, exy = 0;
		if (BULLET->IsCollision("LBomb", &exX, &exy, true, IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), RectMake(0, 0, 0, 0)))
		{
			EFFECTMANAGER->play("bombEffect", exX, exy);
			isOffence = false;

		}
		else if (BULLET->IsCollision("RBomb", &exX, &exy, true, IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), RectMake(0, 0, 0, 0)))
		{
			EFFECTMANAGER->play("bombEffect", exX, exy);
			isOffence = false;

		}

		eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());

		rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

		getDelayTime += TIMEMANAGER->getElapsedTime();
		if (getDelayTime > 1.8f)
		{
			if (!isOffence) move();
			if (getDistance(px, py, x, y) < 200 && !isRight)
			{
				cnt++;
				isOffence = true;
				getDelayTime = 0;
				if (px < x)
				{
					eState = LEFT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
				else if (px > x)
				{
					eState = RIGHT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("bombermanRightOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
			}


			if (getDistance(px, py, x, y) < 200 && isRight)
			{
				cnt++;
				isOffence = true;
				getDelayTime = 0;
				if (px < x)
				{
					eState = LEFT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
				else if (px > x)
				{
					eState = RIGHT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("bombermanRightOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
			}
		}



		enemyCollision();
		epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);
	}

	//KEYANIMANAGER->update();
}

void bomberman::render()
{
	draw();
}

void bomberman::move()
{

	x -= speed;
	getTime += TIMEMANAGER->getElapsedTime();

	if (!eMotion->isPlay() && cnt != 0)
	{
		if (!isRight && eState == LEFT_OFFENCE)
		{
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftMove");
			eMotion->start();
		}
		else if (!isRight && eState == RIGHT_OFFENCE)
		{
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftMove");
			eMotion->start();
		}
		else if (isRight && eState == LEFT_OFFENCE)
		{
			eState = RIGHT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanRightMove");
			eMotion->start();
		}
		else if (isRight && eState == RIGHT_OFFENCE)
		{
			eState = RIGHT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanRightMove");
			eMotion->start();
		}
		cnt = 0;
	}


	if (getTime > 1.8f && cnt == 0)
	{
		if (!isRight)
		{
			isRight = true;
			getTime = 0;
			speed *= -1;
			eState = RIGHT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanRightMove");
			eMotion->start();
		}

		else if (isRight)
		{
			isRight = false;
			getTime = 0;
			speed *= -1;
			eState = LEFT_MOVE;
			*eMotion = *KEYANIMANAGER->findAnimation("bombermanLeftMove");
			eMotion->start();
		}
	}



}

void bomberman::draw()
{
	img->aniRender(getMemDC(), rc.left, rc.top, eMotion);
	//if (eState == LEFT_OFFENCE)
	//{
	//	Lweapon->aniRender(getMemDC(), rc.left, rc.top, eMotion);
	//}
	//else if (eState == RIGHT_OFFENCE)
	//{
	//	Rweapon->aniRender(getMemDC(), rc.left, rc.top, eMotion);
	//}
}


void bomberman::enemyCollision()
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