#include "stdafx.h"
#include "EditScene.h"


EditScene::EditScene()
{
	IMAGEMANAGER->addFrameImage("토마토아이템", PathFile("image", "tomato").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바나나아이템", PathFile("image", "banana").c_str(), 30, 30, 1, 1, true, RGB(255, 0, 255));
}


EditScene::~EditScene()
{
}

HRESULT EditScene::init()
{
	rc = RectMakeCenter(50, 600, 50, 50);
	CAM->CamInit(CENTER_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, WINSIZEX, WINSIZEY, 10);

	Item[0] = new Object(IMAGEMANAGER->findImage("토마토아이템"), 0, 0, "토마토");
	Item[1] = new Object(IMAGEMANAGER->findImage("바나나아이템"), 0, 0, "바나나");
	
	return S_OK;
}

void EditScene::release()
{
}

void EditScene::update()
{
	CamMove(10);
	CAM->CamUpdate(rc, 0, GAMESIZEX, 0, GAMESIZEY);
	Item[0]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x+300, GetCenterPos(CAM->getCamRc()).y-200, 30, 30);
	Item[0]->x = GetCenterPos(Item[0]->rc).x;
	Item[0]->y = GetCenterPos(Item[0]->rc).y;

	Item[1]->rc = RectMakeCenter(GetCenterPos(CAM->getCamRc()).x + 300, GetCenterPos(CAM->getCamRc()).y-150, 30, 30);
	Item[1]->x = GetCenterPos(Item[1]->rc).x;
	Item[1]->y = GetCenterPos(Item[1]->rc).y;
}

void EditScene::render()
{
	IMAGEMANAGER->findImage("스테이지")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	Item[0]->img->render(getMemDC(), Item[0]->rc.left, Item[0]->rc.top);
	Item[1]->img->render(getMemDC(), Item[1]->rc.left, Item[1]->rc.top);
	//CamRender();
}

void EditScene::CamMove(int speed)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= speed;
		rc.right -= speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		rc.left += speed;
		rc.right += speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.bottom -= speed;
		rc.top -= speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.bottom += speed;
		rc.top += speed;
	}
}

void EditScene::CamRender()
{
	Rectangle(getMemDC(), CAM->getViewRc().left, CAM->getViewRc().top, CAM->getViewRc().right, CAM->getViewRc().bottom);
}
