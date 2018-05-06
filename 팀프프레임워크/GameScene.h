#pragma once
#include "gameNode.h"

enum STAGESTATE
{
	IN_GAME,		//������
	STORE,			//����
	BOSS_ENTER,		//������ ����ε�
	BOSS_ROOM,		//������
	FADE_OUT,		//���̵�ƿ�
	BOSS_DIE,
	PLAYER_DIE,
	GAME_OVER		//���ӿ���
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
	//��ü�� �־ ����ϸ� �˴ϴ�.
	RECT				rc;
	STAGESTATE			sState;

	//������ ���巺Ʈ
	RECT				bossEnterRc;

	//���̵�ƿ�
	image*				fadeOut;
	int					alpha;
	int					MetaStageData;
	bool				onceShow = false;

	//ī�޶�ӵ�
	int					camSpeed;

	//�÷��̾� ������ġ
	int					diePosX;
	int					diePosY;

	//Ŭ�����
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

	//�׽�Ʈ��
	void			CamMove  (int speed);
	void			CamRender();

	void			setsState(STAGESTATE state) { sState = state; }

	void			PlayerCollision();
	void			OtherCollision();
	void			PlayerDieSet();

	void			SaveTime();
	void			ShowGameTime();
};

