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
}


GameScene::~GameScene()
{
}

HRESULT GameScene::init()
{
	sState = IN_GAME;
	fadeOut = IMAGEMANAGER->findImage("����ȭ��1");

	_metaKnight = new player;
	_metaKnight->init();

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
		_metaKnight->update(IMAGEMANAGER->findImage("�浹��")->getMemDC());
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
		//������ ����
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
		//CamMove(4);
		//===============�̰� ������ �ʵ���===============//
		CAM->CamUpdate(_metaKnight->getKnightImage().rc, 0, 1600, 0, 800);
		//==============================================//
		PlayerCollision();
		OtherCollision();
		PlayerDieSet();

		////����ü�´ٴ޸� ���ʰ� ���������鼭 
		////�������� ���̵�ƿ����� �Ѿ��
		//if (/*����������*/)
		//{
		//	//����Ʈ�����ֱ�
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
		IMAGEMANAGER->findImage("������")->render(getMemDC(), 0, 0);
		if (KEYMANAGER->isToggleKey(VK_TAB))
			IMAGEMANAGER->findImage("�������浹��")->render(getMemDC(), 0, 0);

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
				//Ŭ������̵���Ű��
				isClear = true;
				SaveTime();
				SCENEMANAGER->changeScene("Ŭ�����");
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
		if (!_im->GetMapItemVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetMapItemVec()[i]->GetRect()))
		{
			if (_im->GetMapItemVec()[i]->GetItemType() == POTION_HP)
			{
				EFFECTMANAGER->play("�����۸�����", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
				//�÷��̾� ü�¿÷��ش�
			}
			else if (_im->GetMapItemVec()[i]->GetItemType() == POTION_MP)
			{
				EFFECTMANAGER->play("�����۸�����", GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).x+15, GetCenterPos(_im->GetMapItemVec()[i]->GetRect()).y+15);
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
		if (!_im->GetGoldItecVec()[i]->GetShowState())continue;
		RECT temp;
		if (IntersectRect(&temp, &_metaKnight->getKnightImage().rc, &_im->GetGoldItecVec()[i]->GetRect()))
		{
			//�÷��̾� �� �÷��ش�
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
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_metaKnight->getKnightImage().rc).x, GetCenterPos(_metaKnight->getKnightImage().rc).y);
			break;
		}
	}

	//�÷��̾� ���ʹ� ��ź

	//�÷��̾� ���ʹ� �θ޶�

	//�÷��̾� ����
	
	//�÷��̾� �����Ѿ�1

	//�÷��̾� �����Ѿ�2
}

void GameScene::OtherCollision()
{
	//�÷��̾� ��Ÿ ���ʹ̵�
	for (int i = 0; i < _em->GetEnemyVec().size(); i++)
	{
		if (_em->GetEnemyVec()[i]->GetisEnemyDie())continue;
		RECT temp;
		if (IntersectRect(&temp, &_em->GetEnemyVec()[i]->getRect(), &_metaKnight->getAttackRc().rc))
		{
			_em->GetEnemyVec()[i]->GetEnemyHp() -= 1;
			EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
			break;
		}
	}

	//�÷��̾� ��Ÿ ����

	//�÷��̾� ��ų1=>�Ѿ��� ���ʹ�
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
				EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
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
				EFFECTMANAGER->play("���ʹ�������", GetCenterPos(_em->GetEnemyVec()[i]->getRect()).x, GetCenterPos(_em->GetEnemyVec()[i]->getRect()).y);
				break;
			}
		}
	}

	//�÷��̾� ��ų1 ����

	//�÷��̾� ��ų2 ���ʹ�

	//�÷��̾� ��ų2 ����
}

void GameScene::PlayerDieSet()
{
	//�÷��̾�ü����0���� ��������
	//if (sState == IN_GAME)
	//{
	//	//�÷��̾� ���̷κ����ش�
	//}
	//else if (sState == BOSS_ROOM)
	//{
	//	//���̵�ƿ��� ���ӿ����� �����ش�

	//	sState = FADE_OUT;
	//	MetaStageData = GAME_OVER;
	//}
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
