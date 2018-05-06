#include "stdafx.h"
#include "Store.h"
#include "player.h"

Store::Store() {}
Store::~Store() {}

HRESULT Store::init()
{
	_image = IMAGEMANAGER->addImage("상점", "image/store.bmp", 715, 413, true, RGB(255, 0, 255));
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	IMAGEMANAGER->addImage("스킬2_ON", "image/Skill2ON.bmp", 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬2_OFF", "image/Skill2.bmp", 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬3_ON", "image/Skill3ON.bmp", 150, 77, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬3_OFF", "image/Skill3.bmp", 150, 77, true, RGB(255, 0, 255));

	for (int i = 0; i < 2; ++i)
	{
		ITEM* item = new ITEM;
		if (i == 0) {
			item->image = IMAGEMANAGER->findImage("스킬2_ON");
			item->salePrice = 1000;
		}
		else {
			item->image = IMAGEMANAGER->findImage("스킬3_ON");
			item->salePrice = 2000;
		}
		item->isSell = false;
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
	BUTTON* backButton = new BUTTON;
	backButton->buttonName = "백버튼";
	backButton->image = IMAGEMANAGER->addImage(
		"백버튼", "image/backButton.bmp", 103, 57, true, RGB(255, 0, 255));
	backButton->x = _rc.left + 30;
	backButton->y = _rc.bottom - 40;
	backButton->rc = RectMakeCenter(backButton->x, backButton->y,
		backButton->image->getWidth(), backButton->image->getHeight());
	backButton->buttonType = BACK_BUTTON;
	_vButton.push_back(backButton);

	_message = "아이템이 가장 저렴한 상점입니다.";
	_index = -1;

	//*_money = 2000;
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
		_vItem[i]->x = _x - 130;
		_vItem[i]->y = _y - 30 + (i * 100);
		_vItem[i]->rc = RectMakeCenter(_vItem[i]->x, _vItem[i]->y, _vItem[i]->image->getWidth(), _vItem[i]->image->getHeight());
		_vItem[i]->image->setX(_vItem[i]->x);
		_vItem[i]->image->setY(_vItem[i]->y);
	}
	for (int i = 0; i < _vButton.size(); ++i)
	{
		if (_vButton[i]->buttonType == BUY_BUTTON) {
			_vButton[i]->x = _x + 200;
			_vButton[i]->y = _y - 5 + (i * 125);
			_vButton[i]->rc = RectMakeCenter(_vButton[i]->x, _vButton[i]->y, _vButton[i]->image->getWidth(), _vButton[i]->image->getHeight());
			_vButton[i]->image->setX(_vButton[i]->x);
			_vButton[i]->image->setY(_vButton[i]->y);
		}
		else if (_vButton[i]->buttonType == BACK_BUTTON) {
			_vButton[i]->x = _rc.left + 60;
			_vButton[i]->y = _rc.bottom - 70;
			_vButton[i]->rc = RectMakeCenter(_vButton[i]->x, _vButton[i]->y, _vButton[i]->image->getWidth(), _vButton[i]->image->getHeight());
			_vButton[i]->image->setX(_vButton[i]->x);
			_vButton[i]->image->setY(_vButton[i]->y);
		}
	}

	BUTTONTYPE buttonType = buttonCollision(&_index);
	if (buttonType == BUY_BUTTON)
	{
		_temp = buyItem(_index, _money);	//_money == 포인터
		//if (_temp != NULL);
			//_gc->getVItem().push_back(_temp);	// 나중에 플레이어가 지닌 아이템 백터에 push_back해줄 것
	}
	else if (buttonType == BACK_BUTTON)
		_gc->setsState(IN_GAME);		// BACK버튼을 누를시, STORE씬 -> IN_GAME씬으로 전환
}

void Store::render()
{
	_image->render(getMemDC(), _rc.left, _rc.top);		// 상점 백그라운드 출력
	for (int i = 0; i < _vItem.size(); ++i)
		_vItem[i]->image->render(getMemDC(), _vItem[i]->rc.left, _vItem[i]->rc.top);		// 상점 아이템 출력
	for (int i = 0; i < _vButton.size(); ++i)
		_vButton[i]->image->render(getMemDC(), _vButton[i]->rc.left, _vButton[i]->rc.top);	// 상점 버튼 출력

	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), _x - 200, _y - 140, _message, strlen(_message));
	//================= 폰트 ===================
	for (int i = 0; i < _vItem.size(); ++i)
	{
		char str[100];
		sprintf(str, "%d", _vItem[i]->salePrice);		// 아이템의 가격 출력

		HFONT font2, oldFont2;
		RECT rcText = RectMake(_vItem[i]->x + 270, _vItem[i]->y - 48 + i * 28, 100, 50);

		font2 = CreateFont(40, 0, 0, 0, 300, 0, 0, 0, DEFAULT_CHARSET,
			OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY,
			DEFAULT_PITCH | FF_SWISS, TEXT("DAVID"));

		oldFont2 = (HFONT)SelectObject(getMemDC(), font2);
		SetTextColor(getMemDC(), RGB(255, 255, 0));
		//=============== 플레이어 골드 ================		
		char str2[100];
		sprintf(str2, "%4d", *_money);
		TextOut(getMemDC(), _x + 130, _y - 155, str2, strlen(str2));
		//==============================================
		SetBkMode(getMemDC(), TRANSPARENT);
		DrawText(getMemDC(), TEXT(str), strlen(str), &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(getMemDC(), oldFont2);
		DeleteObject(font2);
	}
}

BUTTONTYPE Store::buttonCollision(int* pIndex)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		for (int i = 0; i < _vButton.size(); ++i)
			if (_vButton[i]->rc.left <= _ptMouse.x + CAM->getCamRc().left && _ptMouse.x + CAM->getCamRc().left <= _vButton[i]->rc.right)
				if (_vButton[i]->rc.top <= _ptMouse.y + CAM->getCamRc().top && _ptMouse.y + CAM->getCamRc().top <= _vButton[i]->rc.bottom)
				{
					*pIndex = i;
					return _vButton[i]->buttonType;
				}
	return FAIL;	// 버튼이 안눌렸다면
}

ITEM* Store::buyItem(int index, int* money)
//void Store::buyItem(int index, int* money)
{
	if (_vItem[index]->isSell)		// 아이템이 팔렸다면
		_message = "이미 팔린 아이템 입니다.";
	else
	{
		if (*money >= _vItem[index]->salePrice)   // 충분한 돈을 갖고있다면
		{
			*money -= _vItem[index]->salePrice;
			_message = "정상 구매 되었습니다. 감사합니다.";
			_vItem[index]->isSell = true;
			if (index == 0)
			{
				_vItem[index]->image = IMAGEMANAGER->findImage("스킬2_OFF");
				// SkillW 샀을때 ON
				_metaKnight->setSkillHealBool(true);
			}
			else if (index == 1)
			{
				_vItem[index]->image = IMAGEMANAGER->findImage("스킬3_OFF");
				// SkillE 샀을때 ON
				_metaKnight->setSkill2Bool(true);
			}
			return _vItem[index];
		}
		else
			_message = "흥정및 외상은 사절합니다. 훠이~";
	}
	return NULL;
}