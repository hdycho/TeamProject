#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{

}

HRESULT enemy::init()
{
	isEnemyDie = false;
	eHP = 1;
	EFFECTMANAGER->addEffect("dieEffect", PathFile("image", "dieEffect").c_str(), 434, 60, 42, 60, 60, 1, 30);
	return S_OK;
}

HRESULT enemy::init(int x, int y)
{
	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	currentFrameX = currentFrameY = 0;

	//img = IMAGEMANAGER->findImage(imageName);

	rc = RectMakeCenter(position.x, position.y, img->getFrameWidth(), img->getFrameHeight());


	return S_OK;
}

void enemy::release()
{

}

void enemy::update()
{

	if (eHP <= 0 && !isEnemyDie)
	{
		isEnemyDie = true;
		EFFECTMANAGER->play("dieEffect", x, y);
	}
}
void enemy::render()
{
	draw();
}


void enemy::move()
{

}

void enemy::draw()
{
	img->frameRender(getMemDC(), rc.left, rc.top, currentFrameX, currentFrameY);
}

void enemy::enemyCollision()
{
	////¹Ù´Ú
	//if (epCol->RayCastingDownY(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 255, 0, 0));
	//{
	//	epCol->setPosDownY(y);
	//	gravity = 0;
	//}
	//
	////ÃµÀå
	//if (epCol->RayCastingDownY(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 255, 0, 0)) epCol->setPosUpY(y);
	//
	////º®
	//if (epCol->RayCastingX(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 0, 0, 255, 0));
}