#pragma once
#include "gameNode.h"
enum STAGESTATE
{
	IN_GAME,		//게임중
	STORE,			//상점
	BOSS_ROOM,		//보스방
	FADE_OUT		//페이드아웃
};
class GameScene:public gameNode
{
private:
	//객체들 넣어서 사용하면 됩니다.
	RECT rc;
	RECT rc2;

	STAGESTATE sState;
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
};

