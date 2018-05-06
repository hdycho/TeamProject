#pragma once
#include "gameNode.h"

enum STAGESTATE
{
	IN_GAME,		//게임중
	STORE,			//상점
	BOSS_ENTER,		//보스방 입장로딩
	BOSS_ROOM,		//보스방
	FADE_OUT,		//페이드아웃
	BOSS_DIE,
	PLAYER_DIE,
	GAME_OVER		//게임오버
};

class Store;
class player;
class enemyManager;
class ItemManager;
class ObstacleManager;
class PlayerUI;
class Boss;

class GameScene :public gameNode
{

private:
	player*				 _metaKnight;
	enemyManager*		 _em;
	ItemManager*		 _im;
	ObstacleManager*	 _om;
	Store*				 _store;
	PlayerUI*			 _Ui;
	Boss*				 _bs;

private:	
	//객체들 넣어서 사용하면 됩니다.
	RECT				rc;
	STAGESTATE			sState;

	//보스방 입장렉트
	RECT				bossEnterRc;

	//페이드아웃
	image*				fadeOut;
	int					alpha;
	int					MetaStageData;
	bool				onceShow = false;

	//카메라속도
	int					camSpeed;

	//플레이어 죽은위치
	int					diePosX;
	int					diePosY;

	//클리어여부
	bool				isClear;
	float				gameTime;
	int					revertTime;
	int					min;
	int					sec;
public:
	GameScene();
	~GameScene();

	virtual HRESULT init     ();
	virtual void	release  ();
	virtual void	update   ();
	virtual void	render   ();

	//테스트용
	void			CamMove  (int speed);
	void			CamRender();

	void			setsState(STAGESTATE state) { sState = state; }

	void			PlayerCollision();
	void			OtherCollision();
	void			PlayerDieSet();

	void			SaveTime();
	void			ShowGameTime();
};

