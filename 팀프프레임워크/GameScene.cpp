#include "stdafx.h"
#include "GameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "ItemManager.h"

GameScene::GameScene()
{
	//===============총알 셋팅================//
	IMAGEMANAGER->addFrameImage("테스트총알", PathFile("image", "식물1총알").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("총알", IMAGEMANAGER->findImage("테스트총알"), 30, true, 10);
	//=======================================//
	EFFECTMANAGER->addEffect("폭발", PathFile("image", "폭발").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	sState = IN_GAME;
	fadeOut = IMAGEMANAGER->findImage("검은화면");
	rc2 = RectMakeCenter(800, 600, 100, 100);

	_metaKnight = new player;
	_metaKnight->init();

	//===============카메라 셋팅===============//
	CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
	//========================================//

	//================ Store init ==================
	
	_store = new Store;
	_store->setGameSceneAddress(this);

	_store->setLinkMoney(&_money);
	_store->init();
	_em = new enemyManager;
	_em->init();
	_em->setBaby();
	_im = new ItemManager;
	_im->init();

	// player/store link 함수
	_store->setPlayerAddress(_metaKnight);
	_metaKnight->setStoreAddress(_store);
	//==============================================

	// Store/player link 함수 for player (money)
	_store->setLinkMoney(&_metaKnight->_money);
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
		//총알터지는 위치 구하기위해서
		static int x = 0, y = 0;
		if (BULLET->IsCollision("총알", &x, &y, false, NULL, rc2))
		{
			EFFECTMANAGER->play("폭발", x, y);
		}

		//CamMove(4);

		//보스방 입장
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = BOSS_ROOM;
			CAM->CamInit(DYNAMIC_CAMERA, 500, 500, 300, 150, 4);
		}
		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			sState = STORE;
			_store->_message = "아이템이 가장 저렴한 상점입니다.";
			//CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 0);
		}
		//===============이건 만지지 않도록===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
		//==============================================//

		_metaKnight->update();
		_store->update();
		_em->update();
		_im->update();

		//골드 드랍
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_im->DropGold(_metaKnight->getKnightImage().rc.left, _metaKnight->getKnightImage().rc.top, 10, 1);
		}

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
		//===============이건 만지지 않도록===============//
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
		IMAGEMANAGER->findImage("스테이지")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("충돌맵")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

		Rectangle(getMemDC(), rc2.left, rc2.top, rc2.right, rc2.bottom);
		//CamRender();

		_metaKnight->render();
		_em->render();
		_im->render();
	}
	break;
	case STORE:
	{
		_store->render();
	}
	break;
	case BOSS_ROOM:
	{
		IMAGEMANAGER->findImage("보스방")->render(getMemDC(), 0, 0);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("보스방충돌맵")->render(getMemDC(), 0, 0);

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