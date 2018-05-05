#pragma once
#include "gameNode.h"
//=========== Store =============
class Store;
struct ITEM;
//===============================
enum STAGESTATE
{
	IN_GAME,		//������
	STORE,			//����
	BOSS_ENTER,		//������ ����ε�
	BOSS_ROOM,		//������
	FADE_OUT		//���̵�ƿ�
};

class player;
class enemyManager;
class ItemManager;
class ObstacleManager;

class GameScene:public gameNode
{
private:
	//��ü�� �־ ����ϸ� �˴ϴ�.
	RECT rc;
	RECT rc2;
	image*fadeOut;
	STAGESTATE sState;

	player* _metaKnight;
	enemyManager* _em;
	ItemManager* _im;
	ObstacleManager* _om;

	//============== Store ���� ==============
	Store* _store;
	vector<ITEM*> _vItem;  // �÷��̾�� �����ʿ�
	//int	_money;
	//========================================

	//������ ���巺Ʈ
	RECT bossEnterRc;
public:
	GameScene();
	~GameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�׽�Ʈ��
	void CamMove(int speed);
	void CamRender();

	//============== Store �Լ� ==============
	vector<ITEM*> getVItem() { return _vItem; }
	void setsState(STAGESTATE state) { sState = state; }
	//========================================
};

