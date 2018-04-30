#include "stdafx.h"
#include "Store.h"

Store::Store() {}
Store::~Store() {}

HRESULT Store::init()
{
	_image = IMAGEMANAGER->addImage("상점", "image/store.bmp", 715, 413, true, RGB(255, 0, 255));
	//_image = IMAGEMANAGER->findImage("상점");
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	//IMAGEMANAGER->addImage("사과", "image/apple.bmp", 30, 30, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("바나나", "image/banana.bmp", 30, 30, true, RGB(255, 0, 255));
	for (int i = 0; i < 2; ++i)
	{
		ITEM* item = new ITEM;
		//string temp = "아이템";
		//	temp += i;
		//item->itemName = temp;
		if (i == 0) {
			item->image = IMAGEMANAGER->addImage("사과", "image/apple.bmp", 30, 30, true, RGB(255, 0, 255));
			item->salePrice = 1000;
		}
		else {
			item->image = IMAGEMANAGER->addImage("바나나", "image/banana.bmp", 30, 30, true, RGB(255, 0, 255));
			item->salePrice = 2000;
		}
		item->x = _x - 100;
		item->y = _y - 100 + (i * 200);
		item->rc = RectMakeCenter(item->x, item->y,
			item->image->getWidth(), item->image->getHeight());

		item->image->setX(item->x);
		item->image->setY(item->y);
		item->itemType = SKILL_ITEM;
		_vItem.push_back(item);
	}
	for (int i = 0; i < _vItem.size(); ++i)
	{
		BUTTON* Button = new BUTTON;
		string temp = "구매버튼";
		temp += i;
		Button->buttonName = temp;
		Button->image = IMAGEMANAGER->addImage(
			temp, "image/buyButton.bmp", 94, 36, true, RGB(255, 0, 255));
		Button->x = _vItem[i]->x + 200;
		Button->y = _vItem[i]->y;
		Button->rc = RectMakeCenter(Button->x, Button->y,
			Button->image->getWidth(), Button->image->getHeight());
		Button->buttonType = BUY_BUTTON;
		_vButton.push_back(Button);
	}

	_message = "무엇이든 가장 저렴하게 물건을 파는 상점입니다.";
	_index = FAIL;

	return S_OK;
}

void Store::release()
{

}

void Store::update()
{
	_rc = RectMake(CAM->getCamRc().left + 50, CAM->getCamRc().top + 100, _image->getWidth(), _image->getHeight());
	_x = _rc.left + (_rc.right - _rc.left) / 2;
	_y = _rc.top + (_rc.bottom - _rc.top) / 2;
	_image->setX(_x);
	_image->setY(_y);
	for (int i = 0; i < _vItem.size(); ++i)
	{
		_vItem[i]->x = _x - 150;
		_vItem[i]->y = _y - 55 + (i * 125);
		_vItem[i]->rc = RectMakeCenter(_vItem[i]->x, _vItem[i]->y, _vItem[i]->image->getWidth(), _vItem[i]->image->getHeight());
		_vItem[i]->image->setX(_vItem[i]->x);
		_vItem[i]->image->setY(_vItem[i]->y);
	}
	for (int i = 0; i < _vButton.size(); ++i)
	{
		_vButton[i]->x = _x + 200;
		_vButton[i]->y = _y - 5 + (i * 125);
		_vButton[i]->rc = RectMakeCenter(_vButton[i]->x, _vButton[i]->y, _vButton[i]->image->getWidth(), _vButton[i]->image->getHeight());
		_vButton[i]->image->setX(_vButton[i]->x);
		_vButton[i]->image->setY(_vButton[i]->y);
	}

	BUTTONTYPE buttonType = buttonCollision(&_index);
	if (buttonType == BUY_BUTTON)
	{
		_temp = buyItem(_index, _money);	//_money == 포인터
		if (_temp != NULL)
			_gc->getVItem().push_back(_temp);
	}
	else if (buttonType == BACK_BUTTON)
		_gc->setsState(IN_GAME);

	// if (구입 버튼을 눌렀다면)
	//buyItem();
	//if (나가기 버튼을 눌렀다면)
	//break;

}

void Store::render()
{
	// 상점 백그라운드 출력
	_image->render(getMemDC(), _rc.left, _rc.top);
	//_image->render(getMemDC(), _image->getX() - _image->getWidth() / 2, _image->getY() - _image->getHeight() / 2);
	// 상점 아이템 출력
	for (int i = 0; i < _vItem.size(); ++i)
		_vItem[i]->image->render(getMemDC(), _vItem[i]->rc.left, _vItem[i]->rc.top);
	// 상점 버튼 출력
	for (int i = 0; i < _vButton.size(); ++i)
		_vButton[i]->image->render(getMemDC(), _vButton[i]->rc.left, _vButton[i]->rc.top);
	TextOut(getMemDC(), _x - 150, _y - 200, _message, strlen(_message));
}

BUTTONTYPE Store::buttonCollision(int* pIndex)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		for (int i = 0; i < _vButton.size(); ++i)
			if (_vButton[i]->rc.left <= _ptMouse.x + CAM->getCamRc().left && _ptMouse.x + CAM->getCamRc().left <= _vButton[i]->rc.right)
				if (_vButton[i]->rc.top <= _ptMouse.y + CAM->getCamRc().top && _ptMouse.y + CAM->getCamRc().top <= _vButton[i]->rc.bottom)
				{
					*pIndex = i;
					//_message = "정상 구매 되었습니다. 감사합니다.";
					return _vButton[i]->buttonType;
				}
	// 버튼이 안눌렸다면
	return FAIL;
}

ITEM* Store::buyItem(int index, int* money)
{
	//	for (int i = 0; i < _vItem.size(); ++i)
	//		if (itemName == _vItem[i]->itemName)
	if (*money >= _vItem[index]->salePrice)
	{
		*money -= _vItem[index]->salePrice;
		_message = "정상 구매 되었습니다. 감사합니다.";
		return _vItem[index];
	}
	else
		_message = "흥정및 외상은 사절합니다. 훠이~";

	return NULL;
}