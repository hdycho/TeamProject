#include "stdafx.h"
#include "GameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "ItemManager.h"
#include "ObstacleManager.h"
#include "Store.h"
#include "PlayerUI.h"

GameScene::GameScene()
{
	//===============총알 셋팅================//
	IMAGEMANAGER->addFrameImage("테스트총알", PathFile("image", "식물1총알").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("총알", IMAGEMANAGER->findImage("테스트총알"), 30, true, 10);
	//=======================================//
	EFFECTMANAGER->addEffect("폭발", PathFile("image", "폭발").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);
	EFFECTMANAGER->addEffect("아이템먹을때", PathFile("image", "아이템먹었을때").c_str(), 210, 30, 30, 30, 20, 1, 30);
	EFFECTMANAGER->addEffect("동전먹을때", PathFile("image", "동전먹었을때").c_str(), 90, 32, 30, 32, 20, 1, 30);
	EFFECTMANAGER->addEffect("에너미죽을때", PathFile("image", "에너미죽었을때").c_str(), 312, 48, 312 / 6, 48, 20, 1, 30);
	IMAGEMANAGER->addFrameImage("검은화면1", PathFile("image", "검은화면").c_str(), 800, 600, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("로딩화면", PathFile("image", "로딩화면").c_str(), 800, 600, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("로딩창", PathFile("image", "로딩창").c_str(), 3000, 100, 9, 1, true, RGB(255,0,255));
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

	_Ui = new PlayerUI;
	_Ui->init();

	camSpeed = 4;
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
	_em->setMinion();

	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		_em->GetEnemyVec()[i]->setPlayerMemoryAddressLink(_metaKnight);
	}

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
	// player/UI link 함수
	_metaKnight->setUIAddress(_Ui);
	//==============================================

	// Store/player link 함수 for player (money)
	_store->setLinkMoney(&_metaKnight->_money);

	alpha = 0;
	bossEnterRc = RectMakeCenter(18910, 720, 100, 100);
	diePosX = diePosY = 0;
	isClear = false;
	gameTime = 0;
	revertTime = 0;
	min = 0;
	sec = 0;
	return S_OK;
}

void GameScene::release()
{
}

void GameScene::update()
{
	
	switch (sState)
	{
	case PLAYER_DIE:
	{
		_metaKnight->update(IMAGEMANAGER->findImage("충돌맵")->getMemDC());
		_store->update();
		_em->update();
		_im->update();
		_om->update();
		static bool oncePlay = false;

		if (!oncePlay)
		{
			CAM->CamInit(DYNAMIC_CAMERA, diePosX, diePosY, 300, 150, 8);
			oncePlay = true;
		}
		//===============이건 만지지 않도록===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
		//==============================================//

		static POINT pos = { 0,0 };
		pos.x = GetCenterPos(CAM->getCamRc()).x;
		pos.y = GetCenterPos(CAM->getCamRc()).y;

		if (PtInRect(&_metaKnight->getKnightImage().rc, pos))
		{
			pos = { 0,0 };
			oncePlay = false;
			sState = IN_GAME;
			CAM->CamInit(DYNAMIC_CAMERA, GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y, 300, 150, 4);
		}
	}
	break;
	case IN_GAME:
	{
		//CamMove(4);
		//보스방 입장
		gameTime += TIMEMANAGER->getElapsedTime();
	/*	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_im->DropGold(300, 300, 8, 1);
		}*/

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
		OtherCollision();
		PlayerDieSet();
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
		gameTime += TIMEMANAGER->getElapsedTime();
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			sState = IN_GAME;
		}
		_metaKnight->update(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC());
		//CamMove(4);
		//===============이건 만지지 않도록===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, 1600, 0, 800);
		//==============================================//
		PlayerCollision();
		OtherCollision();
		PlayerDieSet();

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
		static int idx = 0;
		if (bossRoomTime > 0.5f)
		{
			bossRoomTime = 0;
			idx++;
		}
		IMAGEMANAGER->findImage("로딩창")->setFrameX(idx);
		if (idx > 8)
		{
			idx = 0;
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
	case PLAYER_DIE:
	{
		IMAGEMANAGER->findImage("스테이지")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("충돌맵")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

		_metaKnight->render();
		_em->render();
		_im->render();
		_om->render();
	}
	break;
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
		ShowGameTime();
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
		ShowGameTime();
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
				//클리어씬이동시키기
				isClear = true;
				SaveTime();
				SCENEMANAGER->changeScene("클리어씬");
			}
		}
		if (MetaStageData == GAME_OVER)
		{
			alpha += 3;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
			if (alpha > 254)
			{
				alpha = 0;
				SaveTime();
				SCENEMANAGER->changeScene("게임오버씬");
			}
		}
	}
	break;
	case BOSS_ENTER:
	{
		//로딩화면보여줌
		IMAGEMANAGER->render("로딩화면", getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top);
		IMAGEMANAGER->frameRender("로딩창", getMemDC(), CAM->getCamRc().left + 250, CAM->getCamRc().top + 500);
		
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
		if (!_im->GetMapItemVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetMapItemVec()[i]->GetRect()))
		{
			if (_im->GetMapItemVec()[i]->GetItemType() == POTION_HP)
			{
				EFFECTMANAGER->play("아이템먹을때", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
				//플레이어 체력올려준다
			}
			else if (_im->GetMapItemVec()[i]->GetItemType() == POTION_MP)
			{
				EFFECTMANAGER->play("아이템먹을때", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
				//플레이어 마나올려준다
			}
			_im->GetMapItemVec()[i]->GetShowState() = false;
			_im->GetMapItemVec()[i]->GetRect() = RectMake(0, 0, 0, 0);
			break;
		}
	}

	//동전
	for (int i = 0; i < _im->GetGoldItecVec().size(); i++)
	{
		if (!_im->GetGoldItecVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetGoldItecVec()[i]->GetRect()))
		{
			//플레이어 돈 올려준다
			EFFECTMANAGER->play("동전먹을때", GetCenterPos(_im->GetGoldItecVec()[i]->GetRect()).x + 15, GetCenterPos(_im->GetGoldItecVec()[i]->GetRect()).y + 15);
			_im->GetGoldItecVec()[i]->GetShowState() = false;
			_im->GetGoldItecVec()[i]->GetRect() = RectMake(0, 0, 0, 0);
			break;
		}
	}
	//===================================//

	//플레이어 에너미
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getKnightImage().rc))
		{
			/*sState = PLAYER_DIE;
			diePosX = _metaKnight->getKnightImage().x;
			diePosY = _metaKnight->getKnightImage().y;
			_metaKnight->getKnightImage().x = 300;
			_metaKnight->getKnightImage().y = 300;
			_metaKnight->getKnightImage().rc = RectMakeCenter(_metaKnight->getKnightImage().x, _metaKnight->getKnightImage().y, 70, 56);*/
			EFFECTMANAGER->play("에너미죽을때", GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y);
			break;
		}
	}

	//플레이어 에너미 폭탄

	//플레이어 에너미 부메랑

	//플레이어 보스
	
	//플레이어 보스총알1

	//플레이어 보스총알2
}

void GameScene::OtherCollision()
{
	//플레이어 평타 에너미들
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getAttackRc().rc))
		{
			_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
			EFFECTMANAGER->play("에너미죽을때", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
			break;
		}
	}

	//플레이어 평타 보스

	//플레이어 스킬1=>총알임 에너미
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		for (int j = 0; j < BULLET->GetBulletVec("bulletSwordRight").size(); j++)
		{
			if (!BULLET->GetBulletVec("bulletSwordRight")[j]->isShot)continue;
			if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &BULLET->GetBulletVec("bulletSwordRight")[j]->rc))
			{
				BULLET->Destroy("bulletSwordRight", j);
				_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
				EFFECTMANAGER->play("에너미죽을때", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
				break;
			}
		}
		for (int j = 0; j < BULLET->GetBulletVec("bulletSwordLeft").size(); j++)
		{
			if (!BULLET->GetBulletVec("bulletSwordLeft")[j]->isShot)continue;
			if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &BULLET->GetBulletVec("bulletSwordLeft")[j]->rc))
			{
				BULLET->Destroy("bulletSwordLeft", j);
				_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
				EFFECTMANAGER->play("에너미죽을때", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
				break;
			}
		}
	}

	//플레이어 스킬1 보스

	//플레이어 스킬2 에너미

	//플레이어 스킬2 보스
}

void GameScene::PlayerDieSet()
{
	//플레이어체력이0보다 낮아지면
	//if (sState == IN_GAME)
	//{
	//	//플레이어 다이로보내준다
	//}
	//else if (sState == BOSS_ROOM)
	//{
	//	//페이드아웃후 게임오버로 보내준다

	//	sState = FADE_OUT;
	//	MetaStageData = GAME_OVER;
	//}
}

void GameScene::SaveTime()
{
	//클리어여부		시간		

	string data;

	FILE*fp = nullptr;
	fopen_s(&fp, "임시저장소.txt", "w+t");

	char term = '\t';
	char next = '\n';
	char end = '@';
	
	data = "ClearState\tTime\n";
	fwrite(data.c_str(), data.size(), 1, fp);

	string clearState;

	if (isClear)
		clearState = "CLEAR";
	else
		clearState = "LOSE";

	data = clearState + term + to_string(min) + term + to_string(sec)+next;
	fwrite(data.c_str(), data.size(), 1, fp);

	fwrite(&end, sizeof(end), 1, fp);
	fclose(fp);
}

void GameScene::ShowGameTime()
{
	gameTime += TIMEMANAGER->getElapsedTime()/4;
	revertTime = (int)gameTime;
	
	min = revertTime / 60;
	sec = revertTime % 60;


	HFONT font, oldFont;
	SetTextColor(getMemDC(), RGB(0,0,0));
	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "휴먼둥근헤드라인");
	oldFont = (HFONT)SelectObject(getMemDC(),font);
	char temp[256];
	if (min < 1)
	{
		if (sec < 10)
		{
			sprintf(temp, "PlayTime: 00:0%d", sec);
			TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top,temp,strlen(temp));
		}
		else
		{
			sprintf(temp, "PlayTime: 00:%d", sec);
			TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, temp, strlen(temp));
		}
	}
	else
	{
		if (min < 10)
		{
			if (sec < 10)
			{
				sprintf(temp, "PlayTime: 0%d:0%d", min,sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, temp, strlen(temp));
			}
			else
			{
				sprintf(temp, "PlayTime: 0%d:%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, temp, strlen(temp));
			}
		}
		else
		{
			if (sec < 10)
			{
				sprintf(temp, "PlayTime: %d:0%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, temp, strlen(temp));
			}
			else
			{
				sprintf(temp, "PlayTime: %d:%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, temp, strlen(temp));
			}
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
