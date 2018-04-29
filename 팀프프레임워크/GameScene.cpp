#include "stdafx.h"
#include "GameScene.h"


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	//===============카메라 셋팅===============//
	CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, 300, 150, 4);
	//========================================//
	
	//===============총알 셋팅================//
	IMAGEMANAGER->addFrameImage("테스트총알", PathFile("image", "식물1총알").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("총알", IMAGEMANAGER->findImage("테스트총알"), 30, true, 10);
	//=======================================//
	
	IMAGEMANAGER->addFrameImage("스테이지2", PathFile("image", "스테이지2").c_str(), 6141, 1000, 1, 1, false, NULL);
	EFFECTMANAGER->addEffect("폭발", PathFile("image", "폭발").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);

	rc = RectMakeCenter(600, 600, 50, 50);
	rc2 = RectMakeCenter(800, 600, 100, 100);

	return S_OK;
}

void GameScene::release()
{
}

void GameScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		BULLET->Shot("총알", GetCenterPos(rc).x, GetCenterPos(rc).y, 0, 0.1, 5);
		BULLET->Shot("총알", GetCenterPos(rc).x, GetCenterPos(rc).y-50, 0, 0.1, 5);
		BULLET->Shot("총알", GetCenterPos(rc).x, GetCenterPos(rc).y-25, 0, 0.1, 5);
	}

	//총알터지는 위치 구하기위해서
	static int x=0, y = 0;
	if (BULLET->IsCollision("총알",&x,&y ,false, NULL, rc2))
	{
		EFFECTMANAGER->play("폭발", x, y);
	}

	CamMove(4);

	//===============이건 만지지 않도록===============//
	CAM->CamUpdate(rc, 0, GAMESIZEX, 0, GAMESIZEY);
	//==============================================//
}

void GameScene::render()
{
	IMAGEMANAGER->findImage("스테이지2")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	Rectangle(getMemDC(), rc2.left, rc2.top, rc2.right, rc2.bottom);
	CamRender();
}

void GameScene::CamMove(int speed)
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

void GameScene::CamRender()
{
	Rectangle(getMemDC(), CAM->getViewRc().left, CAM->getViewRc().top, CAM->getViewRc().right, CAM->getViewRc().bottom);
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}
