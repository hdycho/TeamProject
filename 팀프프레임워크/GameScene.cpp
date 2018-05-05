#include "stdafx.h"
#include "GameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "ItemManager.h"
#include "ObstacleManager.h"
#include "Store.h"

GameScene::GameScene()
{
	//===============�Ѿ� ����================//
	IMAGEMANAGER->addFrameImage("�׽�Ʈ�Ѿ�", PathFile("image", "�Ĺ�1�Ѿ�").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("�Ѿ�", IMAGEMANAGER->findImage("�׽�Ʈ�Ѿ�"), 30, true, 10);
	//=======================================//
	EFFECTMANAGER->addEffect("����", PathFile("image", "����").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	sState = IN_GAME;
	fadeOut = IMAGEMANAGER->findImage("����ȭ��");
	rc2 = RectMakeCenter(800, 600, 100, 100);

	_metaKnight = new player;
	_metaKnight->init();

	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
	//========================================//

	//================ Store init ==================
	
	_store = new Store;
	_store->setGameSceneAddress(this);

	//_store->setLinkMoney(&_money);
	_store->init();
	_em = new enemyManager;
	_em->init();
	_em->setBaby();
	_im = new ItemManager;
	_im->init();
	_om = new ObstacleManager;
	_om->init();

	//bossEnterRc=RectMakeCenter()

	// player/store link �Լ�
	_store->setPlayerAddress(_metaKnight);
	_metaKnight->setStoreAddress(_store);
	//==============================================

	// Store/player link �Լ� for player (money)
	_store->setLinkMoney(&_metaKnight->_money);

	bossEnterRc = RectMakeCenter(18910, 720, 100, 100);
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
		//CamMove(4);
		//������ ����
		RECT temp;
		if (IntersectRect(&temp, &bossEnterRc, &_metaKnight->getKnightImage().rc))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				sState = BOSS_ROOM;
				_metaKnight->getKnightImage().rc = RectMakeCenter(300, 500, 70, 56);
				CAM->CamInit(DYNAMIC_CAMERA, 500, 500, 300, 150, 4);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = BOSS_ROOM;
			_metaKnight->getKnightImage().x = 100;
			_metaKnight->getKnightImage().y = 500;
			_metaKnight->getKnightImage().rc = RectMakeCenter(100, 500, 70, 56);
			CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
		}
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			sState = STORE;
			_store->_message = "�������� ���� ������ �����Դϴ�.";
		}
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
		_store->update();
		_em->update();
		_im->update();
		_om->update();

		//===============�̰� ������ �ʵ���===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
		//==============================================//
	}
	break;
	case STORE:
	{
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			sState = IN_GAME;
		}
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
		_store->update();
	}
	break;
	case BOSS_ROOM:
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = IN_GAME;
		}
		_metaKnight->update(IMAGEMANAGER->findImage("�������浹��")->getMemDC());
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
		//CamRender();

		_metaKnight->render();
		_em->render();
		_im->render();
		_om->render();
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

		_metaKnight->render();
		//CamRender();
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