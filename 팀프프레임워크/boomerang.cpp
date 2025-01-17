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
	epCol->UpdatePosition(GetCenterPos(rc).x, GetCenterPos(rc).y);

	IMAGEMANAGER->addFrameImage("boomerang", PathFile("image", "boomerang").c_str(), 572, 120, 9, 2, true, RGB(255, 0, 255));
	img = new image;
	img->init(PathFile("image", "boomerang").c_str(), 572, 120, 9, 2, true, RGB(255, 0, 255));

	//EFFECTMANAGER->addEffect("boomerangEffect", PathFile("image", "boomerangEffect").c_str(), 224, 22, 28, 22, 60, 1, 30);

	eState = LEFT_MOVE;

	rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

	int leftMove[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftMove", "boomerang", leftMove, 1, 4, true);

	int rightMove[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightMove", "boomerang", rightMove, 1, 4, true);

	int leftOffence[] = { 15,14,13,12,11,10 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftOffence", "boomerang", leftOffence, 6, 7, false);

	int rightOffence[] = { 2,3,4,5,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightOffence", "boomerang", rightOffence, 6, 7, false);

	int leftDie[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangLeftDie", "boomerang", leftDie, 1, 4, true);

	int rightDie[] = { 8 };
	KEYANIMANAGER->addArrayFrameAnimation("boomerangRightDie", "boomerang", rightDie, 1, 4, true);

	eMotion = new animation;
	*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftMove");
	eMotion->start();

	isRight = false;
	isOffence = false;
	isEnemyBulletFire = false;
	speed = 0;
	getTime = 0;
	getDelayTime = 0;
	gravity = 1.0f;

	BULLET->UseCollision("BEffect", 28, 22); //�������� �־������
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


	px = GetCenterPos(_player->getKnightImage().rc).x;
	py = GetCenterPos(_player->getKnightImage().rc).y;




	if (getDistance(px, py, x, y) < 800)
	{
		enemy::update();
		eMotion->frameUpdate(TIMEMANAGER->getElapsedTime());

		rc = RectMakeCenter(x, y, img->getFrameWidth(), img->getFrameHeight());

		if (isEnemyBulletFire && !eMotion->isPlay())
		{
			if (eState == LEFT_OFFENCE)
			{
				BULLET->Shot("BEffect", x, y, PI, 0, 10);
				isEnemyBulletFire = false;
			}
			else if (eState == RIGHT_OFFENCE)
			{
				BULLET->Shot("BEffect", x, y, PI * 2, 0, 10);
				isEnemyBulletFire = false;
			}

		}

		static int bx = 0, by = 0;
		BULLET->IsCollision("BEffect", &bx, &by, true, IMAGEMANAGER->findImage("�浹��")->getMemDC(), RectMake(0, 0, 0, 0));


		getDelayTime += TIMEMANAGER->getElapsedTime();

		if (getDelayTime > 1.6f)
		{
			if (getDistance(px, py, x, y) < 200 && !isRight)
			{

				isOffence = true;
				getDelayTime = 0;
				if (px < x)
				{
					eState = LEFT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
				else if (px > x)
				{
					eState = RIGHT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightOffence");
					eMotion->start();
					isEnemyBulletFire = true;
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
					eState = LEFT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("boomerangLeftOffence");
					eMotion->start();
					isEnemyBulletFire = true;
				}
				else if (px > x)
				{
					eState = RIGHT_OFFENCE;
					*eMotion = *KEYANIMANAGER->findAnimation("boomerangRightOffence");
					eMotion->start();
					isEnemyBulletFire = true;
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
	//Lweapon->aniRender(getMemDC(), rc.left, rc.top, eMotion);
}

void boomerang::enemyCollision()
{
	//�ٴ�
	if (epCol->RayCastingDownY(IMAGEMANAGER->findImage("�浹��")->getMemDC(), 255, 0, 0))
	{
		epCol->setPosDownY(y);
		gravity = 0;
	}
	else
	{
		y += gravity;
		gravity = 1.0f;
	}

	//õ��
	if (epCol->RayCastingUpY(IMAGEMANAGER->findImage("�浹��")->getMemDC(), 255, 0, 0))
	{
		epCol->setPosUpY(y);
	}

	//��
	if (epCol->RayCastingX(IMAGEMANAGER->findImage("�浹��")->getMemDC(), 0, 0, 255, 0))
	{
		speed = 0;
	}
}