#pragma once
#include "gameNode.h"
//=========== Store =============
#include "Store.h"
class Store;
struct ITEM;
//===============================
enum STAGESTATE
{
	IN_GAME,		//게임중
	STORE,			//상점
	BOSS_ROOM,		//보스방
	FADE_OUT		//페이드아웃
};

class player;
class GameScene:public gameNode
{
private:
	//객체들 넣어서 사용하면 됩니다.
	RECT rc;
	RECT rc2;

	STAGESTATE sState;

	player* _metaKnight;

	//============== Store 변수 ==============
	Store* _store;
	vector<ITEM*> _vItem;  // 플레이어와 연동필요
	int	_money;
	//========================================
public:
	GameScene();
	~GameScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//테스트용
	void CamMove(int speed);
	void CamRender();

	//============== Store 함수 ==============
	vector<ITEM*> getVItem() { return _vItem; }
	void setsState(STAGESTATE state) { sState = state; }
	//========================================
};

