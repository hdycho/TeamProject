#include "stdafx.h"
#include "knight.h"


knight::knight()
{
}


knight::~knight()
{

}

HRESULT knight::init()
{
	_image = IMAGEMANAGER->addFrameImage("knight", "knight.bmp", 0, 0, 612, 312, 9, 4, true, RGB(255, 0, 255));

	_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	int rightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightStop", "knight", rightStop, 1, 6, true);

	int leftStop[] = { 9 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftStop", "knight", leftStop, 1, 6, true);

	int rightMove[] = { 1,2,3,4,5,6 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightMove", "knight", rightMove, 6, 10, true);

	int leftMove[] = { 10, 11, 12, 13, 14, 15 };
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftMove", "knight", leftMove, 6, 10, true);

	int rightSit[] = { 18 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSit", "knight", rightSit, 1, 6, true);

	int arrRightAttack[] = { 7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("knightRightAttack", "knight", arrRightAttack, 2, 10, false, rightFire, this);

	_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");

	return S_OK;
}

void knight::release()
{

}

void knight::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightMove");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_knightDirection = KNIGHTDIRECTION_RIGHT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
		_knightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_MOVE;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftMove");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_knightDirection = KNIGHTDIRECTION_LEFT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
		_knightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_knightDirection == KNIGHTDIRECTION_RIGHT_STOP ||
			_knightDirection == KNIGHTDIRECTION_RIGHT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_RIGHT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightAttack");
			_knightMotion->start();
		}
		if (_knightDirection == KNIGHTDIRECTION_LEFT_STOP ||
			_knightDirection == KNIGHTDIRECTION_LEFT_MOVE)
		{
			_knightDirection = KNIGHTDIRECTION_LEFT_ATTACK;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftAttack");
			_knightMotion->start();
		}
	}

	switch (_knightDirection)
	{
		case KNIGHTDIRECTION_RIGHT_STOP:
		break;
		case KNIGHTDIRECTION_LEFT_STOP:
		break;
		case KNIGHTDIRECTION_RIGHT_MOVE:case KNIGHTDIRECTION_RIGHT_MOVE_JUMP:
			_x += KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		
		case KNIGHTDIRECTION_LEFT_MOVE:	case KNIGHTDIRECTION_LEFT_MOVE_JUMP:
			_x -= KNIGHTSPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	
	}

	KEYANIMANAGER->update();

}

void knight::render() 
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _knightMotion);
}


void knight::rightFire(void* obj)	
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_MOVE);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftMove"));
	k->getKnightMotion()->start();

}

void knight::leftFire(void* obj)	
{

}

void knight::rightSitFire(void* obj)
{

}

void knight::leftSitFire(void* obj)
{

}
