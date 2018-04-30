#pragma once
#include "gameNode.h"
#include "Store.h"
class Store;
struct ITEM;

enum STAGESTATE
{
	IN_GAME,		//������
	STORE,			//����
	BOSS_ROOM,		//������
	FADE_OUT		//���̵�ƿ�
};
class GameScene:public gameNode
{
private:
	//��ü�� �־ ����ϸ� �˴ϴ�.
	RECT rc;
	RECT rc2;

	STAGESTATE sState;

//============== Store ���� ==============
	Store* _store;
	vector<ITEM*> _vItem;
	int	_money;
	GameScene* _gc = this;
//========================================
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

