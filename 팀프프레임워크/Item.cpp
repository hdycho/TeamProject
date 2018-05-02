#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}


Item::~Item()
{
}

HRESULT Item::init(image* img, ITEMTYPES itemTypes, float x, float y)
{
	_img = img;
	_itemTypes = itemTypes;
	_x = x;
	_y = y;
	_rc = RectMakeCenter(x, y, _img->getWidth(), _img->getHeight());
	_isShow = false;

	return S_OK;
}

void Item::release()
{

}

void Item::update()
{

}

void Item::render()
{
	_img->render(getMemDC(), _rc.left, _rc.top);
}
