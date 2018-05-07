#include "stdafx.h"
#include "GameScene.h"
#include "player.h"
#include "enemyManager.h"
#include "ItemManager.h"
#include "ObstacleManager.h"
#include "Store.h"
#include "PlayerUI.h"
#include "Boss.h"

GameScene::GameScene()
{
	//===============�Ѿ� ����================//
	IMAGEMANAGER->addFrameImage("�׽�Ʈ�Ѿ�", PathFile("image", "�Ĺ�1�Ѿ�").c_str(), 70, 25, 3, 1, true, RGB(255, 0, 255));
	BULLET->BulletSetting("�Ѿ�", IMAGEMANAGER->findImage("�׽�Ʈ�Ѿ�"), 30, true, 10);
	//=======================================//
	EFFECTMANAGER->addEffect("����", PathFile("image", "����").c_str(), 4500, 150, 4500 / 25, 150, 60, 1, 30);
	EFFECTMANAGER->addEffect("�����۸�����", PathFile("image", "�����۸Ծ�����").c_str(), 210, 30, 30, 30, 20, 1, 30);
	EFFECTMANAGER->addEffect("����������", PathFile("image", "�����Ծ�����").c_str(), 90, 32, 30, 32, 20, 1, 30);
	EFFECTMANAGER->addEffect("���ʹ�������", PathFile("image", "���ʹ��׾�����").c_str(), 312, 48, 312 / 6, 48, 20, 1, 30);
	IMAGEMANAGER->addFrameImage("����ȭ��1", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("�ε�ȭ��", PathFile("image", "�ε�ȭ��").c_str(), 800, 600, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("�ε�â", PathFile("image", "�ε�â").c_str(), 3000, 100, 9, 1, true, RGB(255,0,255));
	EFFECTMANAGER->addEffect("�Ѿ������°�", PathFile("image", "FIRE_EF").c_str(), 1400, 100, 100, 100, 30, 1, 30);
	EFFECTMANAGER->addEffect("��ź�����°�", PathFile("image", "BOMB_EF").c_str(), 4000, 250, 250, 250, 20, 1, 50);
	EFFECTMANAGER->addEffect("�÷��̾����", PathFile("image", "��ֹ�����").c_str(), 700, 100, 100, 100, 25, 1, 50);
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	sState = ENTER_GAME;
	fadeOut = IMAGEMANAGER->findImage("����ȭ��1");

	_metaKnight = new player;
	_metaKnight->init();

	_bs = new Boss;
	_bs->init();
	_bs->SetPlayerLink(_metaKnight);
	
	_Ui = new PlayerUI;
	_Ui->init();

	camSpeed = 4;
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

	// player/store link �Լ�
	_store->setPlayerAddress(_metaKnight);
	_metaKnight->setStoreAddress(_store);
	// player/UI link �Լ�
	_metaKnight->setUIAddress(_Ui);
	//==============================================

	// Store/player link �Լ� for player (money)
	_store->setLinkMoney(&_metaKnight->_money);

	alpha = 255;
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
	case ENTER_GAME:
	{
		alpha -= 3;
		EFFECTMANAGER->play("�÷��̾����", _metaKnight->getKnightImage().x, _metaKnight->getKnightImage().y);
		if (alpha < 1)
		{
			alpha = 0;
			sState = IN_GAME;
		}
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, GAMESIZEX, 0, GAMESIZEY);
	}
	break;
	case PLAYER_DIE:
	{
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
		_store->update();
		_em->update();
		_im->update();
		_om->update();
		static bool oncePlay = false;

		if (!oncePlay)
		{
			CAM->CamInit(DYNAMIC_CAMERA, diePosX, diePosY, 300, 150, 12);
			oncePlay = true;
		}
		//===============�̰� ������ �ʵ���===============//
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
		gameTime += TIMEMANAGER->getElapsedTime();

	
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
			_store->_message = "�������� ���� ������ �����Դϴ�.";
		}
		
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
		_store->update();
		_em->update();
		_im->update();
		_om->update();
		PlayerCollision();
		OtherCollision();
		PlayerDieSet();
		//===============�̰� ������ �ʵ���===============//
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
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
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
		_metaKnight->update(IMAGEMANAGER->findImage("�������浹��")->getMemDC());
		_bs->update();
		//CamMove(4);
		//===============�̰� ������ �ʵ���===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, 1600, 0, 800);
		//==============================================//
		PlayerCollision();
		OtherCollision();
		PlayerDieSet();

		//����ü�´ٴ޸� ���ʰ� ���������鼭 
		//�������� ���̵�ƿ����� �Ѿ��
		if (_bs->GetHp()<0)
		{
			//����Ʈ�����ֱ�
			static float bossDieTime = 0;
			bossDieTime += TIMEMANAGER->getElapsedTime();
			
			if (bossDieTime > 3)
			{
				bossDieTime = 0;
				alpha = 0;
				sState = FADE_OUT;
				MetaStageData = BOSS_DIE;
			}
		}
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
		IMAGEMANAGER->findImage("�ε�â")->setFrameX(idx);
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
	case ENTER_GAME:
	{
		IMAGEMANAGER->findImage("��������")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�浹��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

		//_metaKnight->render();
		_em->render();
		_im->render();
		_om->render();
		//ShowGameTime();
		fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
	}
	break;
	case PLAYER_DIE:
	{
		IMAGEMANAGER->findImage("��������")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�浹��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

		_metaKnight->render();
		_em->render();
		_im->render();
		_om->render();
	}
	break;
	case IN_GAME:
	{
		IMAGEMANAGER->findImage("��������")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�浹��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);

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
		if (alpha < 1)
			alpha = 0;
		else
			alpha -= 4;

		IMAGEMANAGER->findImage("������")->render(getMemDC(), 0, 0);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�������浹��")->render(getMemDC(), 0, 0);

		_metaKnight->render();
		_bs->render();
		ShowGameTime();
		fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
		
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
				alpha = 255;
				sState = BOSS_ROOM;
			}
		}
		if (MetaStageData == BOSS_DIE)
		{
			alpha+=3;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);

			if (alpha > 254)
			{
				alpha = 0;
				//Ŭ������̵���Ű��
				isClear = true;
				SaveTime();
				CAM->CamInit(DYNAMIC_CAMERA, WINSIZEX / 2, WINSIZEY / 2, 300+400, 150, 4);
				SCENEMANAGER->changeScene("Ŭ�����");
			}
		}
		if (MetaStageData == GAME_OVER)
		{
			alpha += 2;
			fadeOut->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
			if (alpha > 254)
			{
				alpha = 0;
				SaveTime();
				CAM->CamInit(DYNAMIC_CAMERA,WINSIZEX/2,WINSIZEY/2+400 , 300, 150, 4);
				SCENEMANAGER->changeScene("���ӿ�����");
			}
		}
	}
	break;
	case BOSS_ENTER:
	{
		//�ε�ȭ�麸����
		IMAGEMANAGER->render("�ε�ȭ��", getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top);
		IMAGEMANAGER->frameRender("�ε�â", getMemDC(), CAM->getCamRc().left + 250, CAM->getCamRc().top + 500);
		
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
	//==========�÷��̾� �������浹===========//
	
	//�丶��,�ٳ���
	for (int i = 0; i < _im->GetMapItemVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_im->GetMapItemVec()[i]->GetRect()))continue;
		if (!_im->GetMapItemVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetMapItemVec()[i]->GetRect()))
		{
			if (_im->GetMapItemVec()[i]->GetItemType() == POTION_HP)
			{
				EFFECTMANAGER->play("�����۸�����", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
				if(_metaKnight->GetHp()<100)
					_metaKnight->GetHp() += 10;
				//�÷��̾� ü�¿÷��ش�
			}
			else if (_im->GetMapItemVec()[i]->GetItemType() == POTION_MP)
			{
				EFFECTMANAGER->play("�����۸�����", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
				if (_metaKnight->GetMp()<100)
					_metaKnight->GetMp() += 10;
				//�÷��̾� �����÷��ش�
			}
			_im->GetMapItemVec()[i]->GetShowState() = false;
			_im->GetMapItemVec()[i]->GetRect() = RectMake(0, 0, 0, 0);
			break;
		}
	}

	//����
	for (int i = 0; i < _im->GetGoldItecVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_im->GetGoldItecVec()[i]->GetRect()))continue;
		if (!_im->GetGoldItecVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetGoldItecVec()[i]->GetRect()))
		{
			//�÷��̾� �� �÷��ش�
			_metaKnight->getMoney() += 200;
			EFFECTMANAGER->play("����������", GetCenterPos(_im->GetGoldItecVec()[i]->GetRect()).x + 15, GetCenterPos(_im->GetGoldItecVec()[i]->GetRect()).y + 15);
			_im->GetGoldItecVec()[i]->GetShowState() = false;
			_im->GetGoldItecVec()[i]->GetRect() = RectMake(0, 0, 0, 0);
			break;
		}
	}
	//===================================//

	//�÷��̾� ���ʹ�
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_em->GetEnemyVec()[i]->getRect()))continue;
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getKnightImage().rc))
		{
			_metaKnight->knightDamaged(_em->GetEnemyVec()[i]->getRect());
			_metaKnight->GetHp() -= 10;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y);
			break;
		}
	}

	//�÷��̾� ���ʹ� ��ź
	//for (int i = 0; BULLET->GetBulletVec("LBomb").size(); i++)
	//{
	//	RECT col;
	//	if (!BULLET->GetBulletVec("LBomb")[i]->isShot)continue;
	//	if (IntersectRect(&col, &BULLET->GetBulletVec("LBomb")[i]->rc, &_metaKnight->getKnightImage().rc))
	//	{
	//		_metaKnight->GetHp() -= 5;
	//		EFFECTMANAGER->play("bombEffect", GetCenterPos(BULLET->GetBulletVec("LBomb")[i]->rc).x, GetCenterPos(BULLET->GetBulletVec("LBomb")[i]->rc).y);
	//		BULLET->Destroy("LBomb", i);
	//	}
	//}
	//for (int i = 0; BULLET->GetBulletVec("RBomb").size(); i++)
	//{
	//	RECT col;
	//	if (!BULLET->GetBulletVec("RBomb")[i]->isShot)continue;
	//	if (IntersectRect(&col, &BULLET->GetBulletVec("RBomb")[i]->rc, &_metaKnight->getKnightImage().rc))
	//	{
	//		_metaKnight->GetHp() -= 5;
	//		EFFECTMANAGER->play("bombEffect", GetCenterPos(BULLET->GetBulletVec("RBomb")[i]->rc).x, GetCenterPos(BULLET->GetBulletVec("RBomb")[i]->rc).y);
	//		BULLET->Destroy("RBomb", i);
	//	}
	//}

	////�÷��̾� ���ʹ� �θ޶�
	//for (int i = 0; BULLET->GetBulletVec("BEffect").size(); i++)
	//{
	//	RECT col;
	//	if (!BULLET->GetBulletVec("BEffect")[i]->isShot)continue;
	//	if (IntersectRect(&col, &BULLET->GetBulletVec("BEffect")[i]->rc, &_metaKnight->getKnightImage().rc))
	//	{
	//		_metaKnight->GetHp() -= 5;
	//		EFFECTMANAGER->play("���ʹ�������", _metaKnight->getKnightImage().x, _metaKnight->getKnightImage().y);
	//		BULLET->Destroy("BEffect", i);
	//	}
	//}

	if (sState == BOSS_ROOM)
	{//�÷��̾� ����
		RECT bCol;
		if (IntersectRect(&bCol, &_metaKnight->getKnightImage().rc, &_bs->GetBossRc()))
		{
			//_metaKnight->knightDamaged(_bs->GetBossRc());
			_metaKnight->GetHp() -= 0.1;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y);
		}

		//�÷��̾� �����Ѿ�1
		for (int i = 0; i < BULLET->GetBulletVec("RGF").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("RGF")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("RGF")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				BULLET->Destroy("RGF", i);
				EFFECTMANAGER->play("�Ѿ������°�", BULLET->GetBulletVec("RGF")[i]->x - 20, BULLET->GetBulletVec("RGF")[i]->y);
				break;
			}
		}
		for (int i = 0; i < BULLET->GetBulletVec("LGF").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("LGF")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("LGF")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				BULLET->Destroy("LGF", i);
				EFFECTMANAGER->play("�Ѿ������°�", BULLET->GetBulletVec("LGF")[i]->x + 20, BULLET->GetBulletVec("LGF")[i]->y);
				break;
			}
		}

		//�÷��̾� �����Ѿ�2
		for (int i = 0; i < BULLET->GetBulletVec("CC").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("CC")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("CC")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				EFFECTMANAGER->play("��ź�����°�", BULLET->GetBulletVec("CC")[i]->x, BULLET->GetBulletVec("CC")[i]->y);
				BULLET->Destroy("CC", i);
				break;
			}
		}
		for (int i = 0; i < BULLET->GetBulletVec("CC1").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("CC1")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("CC1")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				EFFECTMANAGER->play("��ź�����°�", BULLET->GetBulletVec("CC1")[i]->x, BULLET->GetBulletVec("CC1")[i]->y);
				BULLET->Destroy("CC1", i);
				break;
			}
		}
		for (int i = 0; i < BULLET->GetBulletVec("CC2").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("CC2")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("CC2")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				EFFECTMANAGER->play("��ź�����°�", BULLET->GetBulletVec("CC2")[i]->x, BULLET->GetBulletVec("CC2")[i]->y);
				BULLET->Destroy("CC2", i);
				break;
			}
		}
		for (int i = 0; i < BULLET->GetBulletVec("CC3").size(); i++)
		{
			RECT bCol2;
			if (!BULLET->GetBulletVec("CC3")[i]->isShot)continue;
			if (IntersectRect(&bCol2, &_metaKnight->getKnightImage().rc, &BULLET->GetBulletVec("CC3")[i]->rc))
			{
				//����Ʈ �����°�
				_metaKnight->GetHp() -= 10;
				EFFECTMANAGER->play("��ź�����°�", BULLET->GetBulletVec("CC3")[i]->x, BULLET->GetBulletVec("CC3")[i]->y);
				BULLET->Destroy("CC3", i);
				break;
			}
		}
		
		//��������
		RECT bCol3;
		if (IntersectRect(&bCol3, &_metaKnight->getKnightImage().rc, &_bs->GetSwordBox()))
		{
			_metaKnight->GetHp() -= 0.5f;
			_metaKnight->knightDamaged(_bs->GetBossRc());
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y);
		}
	}
}

void GameScene::OtherCollision()
{
	//�÷��̾� ��Ÿ ���ʹ̵�
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_em->GetEnemyVec()[i]->getRect()))continue;
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getAttackRc().rc))
		{
			_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
			_im->DropGold(GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y, 8, 1);
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
			break;
		}
	}

	//�÷��̾� ��Ÿ ����
	RECT bCol4;
	if (IntersectRect(&bCol4, &_metaKnight->getAttackRc().rc, &_bs->GetBossRc()))
	{
		_bs->GetHp() -= 1;
		EFFECTMANAGER->play("�����۸�����", GetCenterPos(_metaKnight->getAttackRc().rc).x, GetCenterPos(_metaKnight->getAttackRc().rc).y);
	}

	//�÷��̾� ��ų1=>�Ѿ��� ���ʹ�
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_em->GetEnemyVec()[i]->getRect()))continue;
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		for (int j = 0; j < BULLET->GetBulletVec("bulletSwordRight").size(); j++)
		{
			if (!BULLET->GetBulletVec("bulletSwordRight")[j]->isShot)continue;
			if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &BULLET->GetBulletVec("bulletSwordRight")[j]->rc))
			{
				_im->DropGold(GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y, 8, 1);
				BULLET->Destroy("bulletSwordRight", j);
				_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
				EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
				break;
			}
		}
		for (int j = 0; j < BULLET->GetBulletVec("bulletSwordLeft").size(); j++)
		{
			if (!BULLET->GetBulletVec("bulletSwordLeft")[j]->isShot)continue;
			if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &BULLET->GetBulletVec("bulletSwordLeft")[j]->rc))
			{
				_im->DropGold(GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y, 8, 1);
				BULLET->Destroy("bulletSwordLeft", j);
				_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
				EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
				break;
			}
		}
	}

	//�÷��̾� ��ų1 ����
	for (int j = 0; j < BULLET->GetBulletVec("bulletSwordRight").size(); j++)
	{
		RECT temp;
		if (!BULLET->GetBulletVec("bulletSwordRight")[j]->isShot)continue;
		if (IntersectRect(&temp, &_bs->GetBossRc(), &BULLET->GetBulletVec("bulletSwordRight")[j]->rc))
		{
			_bs->GetHp() -= 10;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(BULLET->GetBulletVec("bulletSwordRight")[j]->rc).x-30, GetCenterPos(BULLET->GetBulletVec("bulletSwordRight")[j]->rc).y);
			BULLET->Destroy("bulletSwordRight", j);
			break;
		}
	}
	for (int j = 0; j < BULLET->GetBulletVec("bulletSwordLeft").size(); j++)
	{
		RECT temp;
		if (!BULLET->GetBulletVec("bulletSwordLeft")[j]->isShot)continue;
		if (IntersectRect(&temp, &_bs->GetBossRc(), &BULLET->GetBulletVec("bulletSwordLeft")[j]->rc))
		{
			_bs->GetHp() -= 10;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(BULLET->GetBulletVec("bulletSwordLeft")[j]->rc).x+30, GetCenterPos(BULLET->GetBulletVec("bulletSwordLeft")[j]->rc).y);
			BULLET->Destroy("bulletSwordLeft", j);
			break;
		}
	}

	//�÷��̾� ��ų2 ���ʹ�
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		RECT r;
		if (!IntersectRect(&r, &CAM->getCamRc(), &_em->GetEnemyVec()[i]->getRect()))continue;
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getSkill2Left().rc))
		{
			_im->DropGold(GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y, 8, 1);
			_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
			break;
		}
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getSkill2Right().rc))
		{
			_im->DropGold(GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y, 8, 1);
			_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
			break;
		}

	}

	//�÷��̾� ��ų2 ����
	RECT rec1;
	if (IntersectRect(&rec1, &_metaKnight->getSkill2Left().rc, &_bs->GetBossRc()))
	{
		_bs->GetHp() -= 2;
	}
	RECT rec2;
	if (IntersectRect(&rec2, &_metaKnight->getSkill2Right().rc, &_bs->GetBossRc()))
	{
		_bs->GetHp() -= 2;
	}
}

void GameScene::PlayerDieSet()
{
	//�÷��̾�ü����0���� ��������
	if (sState == IN_GAME)
	{
		if (_metaKnight->GetHp() < 0)
		{
			sState = PLAYER_DIE;
			_metaKnight->GetHp() = 100;
			_metaKnight->GetMp() = 100;
			diePosX = _metaKnight->getKnightImage().x;
			diePosY = _metaKnight->getKnightImage().y;
			_metaKnight->getKnightImage().x = 300;
			_metaKnight->getKnightImage().y = 200;
		}
		//�÷��̾� ���̷κ����ش�
	}
	else if (sState == BOSS_ROOM)
	{
		//���̵�ƿ��� ���ӿ����� �����ش�
		if (_metaKnight->GetHp() <= 0)
		{
			sState = FADE_OUT;
			MetaStageData = GAME_OVER;
		}
	}
}

void GameScene::SaveTime()
{
	//Ŭ�����		�ð�		
	string data;

	FILE*fp = nullptr;
	fopen_s(&fp, "�ӽ������.txt", "w+t");

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
	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�޸յձ�������");
	oldFont = (HFONT)SelectObject(getMemDC(),font);
	char temp[256];
	if (min < 1)
	{
		if (sec < 10)
		{
			sprintf(temp, "PlayTime: 00:0%d", sec);
			TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top+100,temp,strlen(temp));
		}
		else
		{
			sprintf(temp, "PlayTime: 00:%d", sec);
			TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top + 100, temp, strlen(temp));
		}
	}
	else
	{
		if (min < 10)
		{
			if (sec < 10)
			{
				sprintf(temp, "PlayTime: 0%d:0%d", min,sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top + 100, temp, strlen(temp));
			}
			else
			{
				sprintf(temp, "PlayTime: 0%d:%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top + 100, temp, strlen(temp));
			}
		}
		else
		{
			if (sec < 10)
			{
				sprintf(temp, "PlayTime: %d:0%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top + 100, temp, strlen(temp));
			}
			else
			{
				sprintf(temp, "PlayTime: %d:%d", min, sec);
				TextOut(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top + 100, temp, strlen(temp));
			}
		}
	}
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
