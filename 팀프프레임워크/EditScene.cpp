#include "stdafx.h"
#include "EditScene.h"


EditScene::EditScene()
{
	IMAGEMANAGER->addFrameImage("토마토아이템", PathFile("image", "tomato").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바나나아이템", PathFile("image", "banana").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("에딧창", PathFile("image", "에딧창").c_str(), 250, 417, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("세이브버튼", PathFile("image", "버튼").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무", PathFile("image", "나무장애물").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쇠", PathFile("image", "쇠장애물").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폭탄", PathFile("image", "폭탄장애물").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
}


EditScene::~EditScene()
{
}

HRESULT EditScene::init()
{
	clickObj = nullptr;
	rc = RectMakeCenter(50, 600, 10, 10);
	CAM->CamInit(CENTER_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, WINSIZEX, WINSIZEY, 10);

	Item[0] = new Object(IMAGEMANAGER->findImage("토마토아이템"), 0, 0, "토마토");
	Item[1] = new Object(IMAGEMANAGER->findImage("바나나아이템"), 0, 0, "바나나");
	Item[2] = new Object(IMAGEMANAGER->findImage("나무"), 0, 0, "나무");
	Item[3] = new Object(IMAGEMANAGER->findImage("쇠"), 0, 0, "쇠");
	Item[4] = new Object(IMAGEMANAGER->findImage("폭탄"), 0, 0, "폭탄");

	save = new button;
	save->Init(IMAGEMANAGER->findImage("세이브버튼"), "SAVE", 0, 0);

	Loby = new button;
	Loby->Init(IMAGEMANAGER->findImage("세이브버튼"), "LOBY", 0, 0);

	fadeout = IMAGEMANAGER->findImage("검은화면");
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
		SCENEMANAGER->changeScene("시작씬");
	}

	SelectObj();
	DropObj();
	SaveObj();
}

void EditScene::render()
{
	IMAGEMANAGER->findImage("스테이지")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
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
	font = CreateFont(30, 0, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("궁서체"));
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
	IMAGEMANAGER->findImage("에딧창")->render(getMemDC(), GetCenterPos(CAM->getCamRc()).x + 150, GetCenterPos(CAM->getCamRc()).y - 200);

	for (int i = 0; i<5; i++)
		Item[i]->img->render(getMemDC(), Item[i]->rc.left, Item[i]->rc.top);


	HFONT font, oldFont;
	font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT("궁서체"));
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
		fopen_s(&fp, "오브젝트데이터.txt", "w+t");

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
