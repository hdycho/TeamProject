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

