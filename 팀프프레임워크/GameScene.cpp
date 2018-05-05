#include "stdafx.h"
#include "GameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "ItemManager.h"
#include "ObstacleManager.h"
#include "Store.h"

GameScene::GameScene()
{
	//===============총알 셋팅================//
	IMAGEMANAGER->addFrameImage("테스트총알", PathFile("image", "식물1총알").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("총알", IMAGEMANAGER->findImage("테스트총알"), 30, true, 10);
	//=======================================//
	EFFECTMANAGER->addEffect("폭발", PathFile("image", "폭발").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);
	IMAGEMANAGER->addFrameImage("검은화면1", PathFile("image", "검은화면").c_str(), 800, 600, 1, 1, false, NULL);
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	sState = IN_GAME;
	fadeOut = IMAGEMANAGER->findImage("검은화면1");

	_metaKnight = new player;
	_metaKnight->init();

	//===============카메라 셋팅===============//
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

	for (int i = 0; i < _om->GetObjVec().size(); i++)
	{
		_om->GetObjVec()[i]->LinkPlayer(_metaKnight);
	}

	// player/store link 함수
	_store->setPlayerAddress(_metaKnight);
	_metaKnight->setStoreAddress(_store);
	//==============================================

	// Store/player link 함수 for player (money)
	_store->setLinkMoney(&_metaKnight->_money);

	alpha = 0;
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
		//보스방 입장
		RECT temp;
		if (IntersectRect(&temp, &bossEnterRc, &_metaKnight->getKnightImage().rc))
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				sState = FADE_OUT;
				_metaKnight->getKnightImage().x = 300;
				_metaKnight->getKnightImage().y = 500;
				_metaKnight->getKnightImage().rc = RectMakeCenter(300, 500, 70, 56);
				MetaStageData = BOSS_ENTER;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = FADE_OUT;
			_metaKnight->getKnightImage().x = 300;
			_metaKnight->getKnightImage().y = 500;
			_metaKnight->getKnightImage().rc = RectMakeCenter(300, 500, 70, 56);
			MetaStageData = BOSS_ENTER;
		}
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			alpha = 20;
			sState = STORE;
			_store->_message = "아이템이 가장 저렴한 상점입니다.";
		}
		_metaKnight->update(IMAGEMANAGER->findImage("충돌맵")->getMemDC());
		_store->update();
		_em->update();
		_im->update();
		_om->update();
		PlayerCollision();
		//===============이건 만지지 않도록===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
		//==============================================//
	}
	break;
	case STORE:
	{
		if (KEYMANAGER->isOnceKeyDown('R'))
		{
			onceShow = false;
			alpha = 0;
			sState = IN_GAME;
		}
		_metaKnight->update(IMAGEMANAGER->findImage("충돌맵")->getMemDC());
		_store->update();
	}
	break;
	case BOSS_ROOM:
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = IN_GAME;
		}
		_metaKnight->update(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC());
		//CamMove(4);
		//===============이건 만지지 않도록===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, 1600, 0, 800);
		//==============================================//


		////보스체력다달면 몇초간 보스터지면서 
		////다터지고 페이드아웃으로 넘어가고
		//if (/*보스죽으면*/)
		//{
		//	//이펙트보여주기
		//	static float bossDieTime = 0;
		//	bossDieTime += TIMEMANAGER->getElapsedTime();
		//	
		//	if (bossDieTime > 3)
		//	{
		//		bossDieTime = 0;
		//		alpha = 0;
		//		sState = FADE_OUT;
		//		MetaStageData = BOSS_DIE;
		//	}
		//}
	}
	break;
	case BOSS_ENTER:
	{
		static float bossRoomTime = 0;
		bossRoomTime += TIMEMANAGER->getElapsedTime();

		if (bossRoomTime > 3)
		{
			bossRoomTime = 0;
			alpha = 0;
			sState = FADE_OUT;
			MetaStageData = BOSS_ROOM;
		}
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

		//CamRender();

		_metaKnight->render();
		_em->render();
		_im->render();
		_om->render();
	}
	break;
	case STORE:
	{	
		if (!onceShow)
		{
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, 200);
			onceShow = true;
		}
		_store->render();
	}
	break;
	case BOSS_ROOM:
	{
		IMAGEMANAGER->findImage("보스방")->render(getMemDC(), 0, 0);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("보스방충돌맵")->render(getMemDC(), 0, 0);

		_metaKnight->render();
		//CamRender();
	}
	break;
	case FADE_OUT:
	{
		if (MetaStageData == BOSS_ENTER)
		{
			alpha+=3;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
			
			if (alpha > 254)
			{
				alpha = 0;
				sState = BOSS_ENTER;
			}
		}
		if (MetaStageData == BOSS_ROOM)
		{
			alpha+=3;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);

			if (alpha > 254)
			{
				alpha = 0;
				sState = BOSS_ROOM;
				CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
			}
		}
		if (MetaStageData == BOSS_DIE)
		{
			alpha+=3;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);

			if (alpha > 254)
			{
				alpha = 0;
				//씬이동시키기
			}
		}
	}
	break;
	case BOSS_ENTER:
	{
		//로딩화면보여줌

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

void GameScene::PlayerCollision()
{
	//==========플레이어 아이템충돌===========//
	
	//토마토,바나나
	for (int i = 0; i < _im->GetMapItemVec().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetMapItemVec()[i]->GetRect()))
		{
			if (_im->GetMapItemVec()[i]->GetItemType() == POTION_HP)
			{
				//아이템 먹을때 이펙트
				//플레이어 체력올려준다
			}
			else if (_im->GetMapItemVec()[i]->GetItemType() == POTION_MP)
			{
				//아이템 먹을때 이펙트
				//플레이어 마나올려준다
			}
			_im->GetMapItemVec()[i]->GetShowState() = false;
		}
	}

	//동전
	for (int i = 0; i < _im->GetGoldItecVec().size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetGoldItecVec()[i]->GetRect()))
		{
			//동전먹는이펙트
			//플레이어 돈 올려준다
			_im->GetGoldItecVec()[i]->GetShowState() = false;
		}
	}
	//===================================//

	//플레이어 에너미

	//플레이어 에너미 폭탄

	//플레이어 에너미 부메랑

	//플레이어 보스
	
	//플레이어 보스총알1

	//플레이어 보스총알2
}

void GameScene::OtherCollision()
{
	//플레이어 평타 에너미들

	//플레이어 평타 보스

	//플레이어 스킬1=>총알임 에너미

	//플레이어 스킬1 보스

	//플레이어 스킬2 에너미

	//플레이어 스킬2 보스
}
