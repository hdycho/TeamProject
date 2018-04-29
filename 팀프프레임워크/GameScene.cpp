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
	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(rc).x, GetCenterPos(rc).y, 300, 150, 4);
	//========================================//
	
	//===============�Ѿ� ����================//
	IMAGEMANAGER->addFrameImage("�׽�Ʈ�Ѿ�", PathFile("image", "�Ĺ�1�Ѿ�").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("�Ѿ�", IMAGEMANAGER->findImage("�׽�Ʈ�Ѿ�"), 30, true, 10);
	//=======================================//
	
	IMAGEMANAGER->addFrameImage("��������2", PathFile("image", "��������2").c_str(), 6141, 1000, 1, 1, false, NULL);
	EFFECTMANAGER->addEffect("����", PathFile("image", "����").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);

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
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y, 0, 0.1, 5);
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y-50, 0, 0.1, 5);
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y-25, 0, 0.1, 5);
	}

	//�Ѿ������� ��ġ ���ϱ����ؼ�
	static int x=0, y = 0;
	if (BULLET->IsCollision("�Ѿ�",&x,&y ,false, NULL, rc2))
	{
		EFFECTMANAGER->play("����", x, y);
	}

	CamMove(4);

	//===============�̰� ������ �ʵ���===============//
	CAM->CamUpdate(rc, 0, GAMESIZEX, 0, GAMESIZEY);
	//==============================================//
}

void GameScene::render()
{
	IMAGEMANAGER->findImage("��������2")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
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
