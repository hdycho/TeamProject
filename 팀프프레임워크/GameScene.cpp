#include "stdafx.h"
#include "GameScene.h"
#include "player.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	//===============�Ѿ� ����================//
	IMAGEMANAGER->addFrameImage("�׽�Ʈ�Ѿ�", PathFile("image", "�Ĺ�1�Ѿ�").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("�Ѿ�", IMAGEMANAGER->findImage("�׽�Ʈ�Ѿ�"), 30, true, 10);
	//=======================================//

	IMAGEMANAGER->addFrameImage("�浹��", PathFile("image", "�浹��").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("��������", PathFile("image", "��������").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("������", PathFile("image", "������").c_str(), 1600, 800, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("�������浹��", PathFile("image", "�������浹��").c_str(), 1600, 800, 1, 1, false, NULL);
	EFFECTMANAGER->addEffect("����", PathFile("image", "����").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);

	sState = IN_GAME;

	rc2 = RectMakeCenter(800, 600, 100, 100);

	_metaKnight = new player;
	_metaKnight->init();

	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
	//========================================//

	//================ Store init ==================
	_money = 2000;			// �Ӵϴ� �÷��̾�� ���� �ʿ�
	_store = new Store;
	_store->setGameSceneAddress(this);
	_store->setLinkMoney(&_money);
	_store->init();
	//==============================================
	return S_OK;
}

void GameScene::release()
{
}

void GameScene::update()
{
	switch (sState)
	{
	case IN_GAME:
	{
		/*if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y, 0, 0.1, 5);
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y - 50, 0, 0.1, 5);
		BULLET->Shot("�Ѿ�", GetCenterPos(rc).x, GetCenterPos(rc).y - 25, 0, 0.1, 5);
		}*/

		//�Ѿ������� ��ġ ���ϱ����ؼ�
		static int x = 0, y = 0;
		if (BULLET->IsCollision("�Ѿ�", &x, &y, false, NULL, rc2))
		{
			EFFECTMANAGER->play("����", x, y);
		}

		//CamMove(4);

		//������ ����
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = BOSS_ROOM;
			CAM->CamInit(DYNAMIC_CAMERA, 500, 500, 300, 150, 4);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			sState = STORE;
			_store->_message = "�������� ���� ������ �����Դϴ�.";
			//CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 0);
		}
		//===============�̰� ������ �ʵ���===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
		//==============================================//

		_metaKnight->update();
		_store->update();
	}
	break;
	case STORE:
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			sState = IN_GAME;
		}
		_store->update();
	}
	break;
	case BOSS_ROOM:
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = IN_GAME;
		}

		//CamMove(4);
		//===============�̰� ������ �ʵ���===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, 1600, 0, 800);
		//==============================================//
	}
	break;
	case FADE_OUT:
	{

	}
	break;
	}
}

void GameScene::render()
{
	switch (sState)
	{
	case IN_GAME:
	{
		IMAGEMANAGER->findImage("��������")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�浹��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

		Rectangle(getMemDC(), rc2.left, rc2.top, rc2.right, rc2.bottom);
		CamRender();

		_metaKnight->render();
	}
	break;
	case STORE:
	{
		_store->render();
	}
	break;
	case BOSS_ROOM:
	{
		IMAGEMANAGER->findImage("������")->render(getMemDC(), 0, 0);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�������浹��")->render(getMemDC(), 0, 0);

		CamRender();
	}
	break;
	case FADE_OUT:
	{

	}
	break;
	}


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
	//Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
}