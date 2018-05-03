#include "stdafx.h"
#include "button.h"
button::button()
	:img(nullptr), bState(BUTTON_NULL), isClick(false)
{
}
button::~button()
{
}

HRESULT button::Init(image * img, string bName, float x, float y)
{
	this->img = new image;
	*(this->img) = *img;

	this->x = x;
	this->y = y;
	rc = RectMakeCenter(x, y, this->img->getFrameWidth(), this->img->getFrameHeight());
	frameX = 0;
	this->img->setFrameX(frameX);

	bState = BUTTON_UP;
	buttonName = bName;

	return S_OK;
}

void button::Render()
{
	if (bState == BUTTON_DOWN)
		img->frameRender(getMemDC(), rc.left, rc.top, 0, 1);
	else
		img->frameRender(getMemDC(), rc.left, rc.top, 0, 0);
	ButtonNameDraw();


	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}

void button::Update(int key)
{

	if (PtInRect(&rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(key))
		{
			bState = BUTTON_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(key) && bState == BUTTON_DOWN)
		{
			bState = BUTTON_UP;
			isClick = true;
		}
	}
	else
		bState = BUTTON_NULL;

	if (bState == BUTTON_NULL)
	{
		if (KEYMANAGER->isStayKeyDown(key))
			isClick = false;
	}
}

void button::Release()
{
}

void button::ButtonNameDraw()
{
	HFONT font, oldFont;
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("±Ã¼­Ã¼"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetBkMode(getMemDC(), TRANSPARENT);
	DrawText(getMemDC(), buttonName.c_str(), strlen(buttonName.c_str()), &rc,
		DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
