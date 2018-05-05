#include "stdafx.h"
#include "EditScene.h"


EditScene::EditScene()
{
	IMAGEMANAGER->addFrameImage("�丶�������", PathFile("image", "tomato").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٳ���������", PathFile("image", "banana").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����â", PathFile("image", "����â").c_str(), 250, 417, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("���̺��ư", PathFile("image", "��ư").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����", PathFile("image", "������ֹ�").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��", PathFile("image", "����ֹ�").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ź", PathFile("image", "��ź��ֹ�").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
}


EditScene::~EditScene()
{
}

HRESULT EditScene::init()
{
	clickObj = nullptr;
	rc = RectMakeCenter(50, 600, 10, 10);
	CAM->CamInit(CENTER_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, WINSIZEX, WINSIZEY, 10);

	Item[0] = new Object(IMAGEMANAGER->findImage("�丶�������"), 0, 0, "�丶��");
	Item[1] = new Object(IMAGEMANAGER->findImage("�ٳ���������"), 0, 0, "�ٳ���");
	Item[2] = new Object(IMAGEMANAGER->findImage("����"), 0, 0, "����");
	Item[3] = new Object(IMAGEMANAGER->findImage("��"), 0, 0, "��");
	Item[4] = new Object(IMAGEMANAGER->findImage("��ź"), 0, 0, "��ź");

	save = new button;
	save->Init(IMAGEMANAGER->findImage("���̺��ư"), "SAVE", 0, 0);

	Loby = new button;
	Loby->Init(IMAGEMANAGER->findImage("���̺��ư"), "LOBY", 0, 0);

	fadeout = IMAGEMANAGER->findImage("����ȭ��");
	alpha = 0;

	return S_OK;
}

void EditScene::release()
{
}

void EditScene::update()
{
	CamMove(10);
	CAM->CamUpdate(rc, 0, GAMESIZEX, 0, GAMESIZEY);

	Item[0]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 240, GetCenterPos(CAM->getCamRc()).y - 100, 30, 30);
	Item[0]->x = GetCenterPos(Item[0]->rc).x;
	Item[0]->y = GetCenterPos(Item[0]->rc).y;

	Item[1]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 300, GetCenterPos(CAM->getCamRc()).y - 100, 30, 30);
	Item[1]->x = GetCenterPos(Item[1]->rc).x;
	Item[1]->y = GetCenterPos(Item[1]->rc).y;

	Item[2]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 230, GetCenterPos(CAM->getCamRc()).y, 30, 30);
	Item[2]->x = GetCenterPos(Item[1]->rc).x;
	Item[2]->y = GetCenterPos(Item[1]->rc).y;

	Item[3]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 270, GetCenterPos(CAM->getCamRc()).y, 30, 30);
	Item[3]->x = GetCenterPos(Item[1]->rc).x;
	Item[3]->y = GetCenterPos(Item[1]->rc).y;

	Item[4]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 310, GetCenterPos(CAM->getCamRc()).y, 30, 30);
	Item[4]->x = GetCenterPos(Item[1]->rc).x;
	Item[4]->y = GetCenterPos(Item[1]->rc).y;

	save->GetRect() = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 275, GetCenterPos(CAM->getCamRc()).y - 200, 250, 60);
	save->Update(VK_LBUTTON, false);

	Loby->GetRect() = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 275, GetCenterPos(CAM->getCamRc()).y + 220, 250, 60);
	Loby->Update(VK_LBUTTON, false);

	if (Loby->IsClick())
	{
		alpha += 4;
	}
	if (alpha > 254)
	{
		SCENEMANAGER->changeScene("���۾�");
	}

	SelectObj();
	DropObj();
	SaveObj();
}

void EditScene::render()
{
	IMAGEMANAGER->findImage("��������")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);

	for (int i = 0; i < objVec.size(); i++)
	{
		if (objVec[i]->isShow)
			objVec[i]->img->render(getMemDC(), objVec[i]->rc.left, objVec[i]->rc.top);
	}

	if (KEYMANAGER->isToggleKey('I'))
	{
		EditDraw();
		save->Render();
		Loby->Render();
	}

	for (int i = 0; i < 5; i++)
	{
		if (Item[i]->isClick)
			DrawRect(getMemDC(), Item[i]->rc, 5, RGB(0, 0, 255));
	}

	if (clickObj != nullptr)
	{
		if (clickObj->isMove)
			clickObj->img->render(getMemDC(), clickObj->x, clickObj->y);
	}

	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("�ü�ü"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(0, 255, 255));
	char temp[256];
	sprintf(temp, "[x:%d y:%d]", GetCenterPos(rc).x, GetCenterPos(rc).y);
	TextOut(getMemDC(), rc.left, rc.top - 30, temp, strlen(temp));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	fadeout->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
}

void EditScene::SelectObj()
{
	static POINT mPos = { 0,0 };
	mPos.x = _ptMouse.x;
	mPos.y = _ptMouse.y;
	mPos.x += CAM->getCamRc().left;
	mPos.y += CAM->getCamRc().top;

	if (clickObj != nullptr)
	{
		if (clickObj->isMove)
		{
			clickObj->x = mPos.x - 15;
			clickObj->y = mPos.y - 15;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&Item[i]->rc, mPos))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				Item[i]->isClick = true;
				Item[i]->isMove = true;
				clickObj = new Object(
					Item[i]->img,
					Item[i]->x,
					Item[i]->y,
					Item[i]->objName);
				clickObj->isMove = true;
			}
		}
		else
		{
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				Item[i]->isClick = false;
		}
	}
}

void EditScene::DropObj()
{
	if (clickObj != nullptr)
	{
		if (clickObj->isMove)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				clickObj->isMove = false;
				Object*pushObj = new Object(
					clickObj->img,
					clickObj->x,
					clickObj->y,
					clickObj->objName);
				pushObj->isShow = true;
				pushObj->rc = RectMakeCenter(pushObj->x + 15, pushObj->y + 15, 30, 30);
				objVec.push_back(pushObj);
			}
		}
	}
}

void EditScene::EditDraw()
{
	IMAGEMANAGER->findImage("����â")->render(getMemDC(), GetCenterPos(CAM->getCamRc()).x + 150, GetCenterPos(CAM->getCamRc()).y - 200);

	for (int i = 0; i<5; i++)
		Item[i]->img->render(getMemDC(), Item[i]->rc.left, Item[i]->rc.top);


	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("�ü�ü"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	TextOut(getMemDC(), Item[0]->rc.left + 13, Item[0]->rc.top - 53, "ITEM", strlen("ITEM"));
	TextOut(getMemDC(), Item[0]->rc.left + 13, Item[0]->rc.top + 53, "TILE", strlen("TILE"));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

}

void EditScene::SaveObj()
{
	if (save->IsClick())
	{
		FILE*fp = nullptr;
		fopen_s(&fp, "������Ʈ������.txt", "w+t");

		char Token = '\t';
		char Next = '\n';
		char EndToken = '@';

		string Temp;
		Temp = "ObjectName\tPosX\tPosY\n";
		fwrite(Temp.c_str(), Temp.size(), 1, fp);

		for (int i = 0; i < objVec.size(); i++)
		{
			Temp = objVec[i]->objName +
				Token + to_string(objVec[i]->x) +
				Token + to_string(objVec[i]->y) +
				Next;
			fwrite(Temp.c_str(), Temp.size(), 1, fp);
		}
		fwrite(&EndToken, sizeof EndToken, 1, fp);
		fclose(fp);
	}
}


void EditScene::CamMove(int speed)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		rc.left -= speed;
		rc.right -= speed;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		rc.left += speed;
		rc.right += speed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		rc.bottom -= speed;
		rc.top -= speed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		rc.bottom += speed;
		rc.top += speed;
	}
}

void EditScene::CamRender()
{
	Rectangle(getMemDC(), CAM->getViewRc().left, CAM->getViewRc().top, CAM->getViewRc().right, CAM->getViewRc().bottom);
}
