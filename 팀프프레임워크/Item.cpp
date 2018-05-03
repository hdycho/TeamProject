#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}


Item::~Item()
{
}

HRESULT Item::init(image* img, ITEMTYPES itemTypes, int x, int y)
{
	_img = img;
	_itemTypes = itemTypes;
	_rc = RectMakeCenter(x, y, _img->getWidth(), _img->getHeight());
	_isShow = false;
	_isCollision = false;
	_pc = new PixelCol;
	_pc->init(20, 20);
	_count = _index = 0;
	gState = GOLD_AIR;
	gravity = 0.1f;
	jumpPower = 0;
	return S_OK;
}

void Item::release()
{

}

void Item::update()
{
	_pc->UpdatePosition(GetCenterPos(_rc).x, GetCenterPos(_rc).y);
	if (_pc->RayCastingDownY(IMAGEMANAGER->findImage("Ãæµ¹¸Ê")->getMemDC(), 255, 0, 0))
	{
		_isCollision = true;
	}
	else
	{
		_isCollision = false;
	}

	_count++;

	if (_count > 3)
	{
		if (_itemTypes == GOLD_ITEM)
		{
			IMAGEMANAGER->findImage("AniGold")->setFrameX(_index);
			_index++;
			if (_index > 5) _index = 0;
		}
		_count = 0;
	}
}

void Item::render()
{
	if (_itemTypes == POTION_HP || _itemTypes == POTION_MP)
	{
		_img->render(getMemDC(), _rc.left, _rc.top);
	}
	if (_itemTypes == GOLD_ITEM)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top);
	}
}

void Item::GoldUpdate()
{
	if (_itemTypes == GOLD_ITEM)
	{
		switch (gState)
		{
		case GOLD_AIR:
		{

		}
		break;
		case GOLD_GROUND:
		{

		}
		break;
		}
	}
}
