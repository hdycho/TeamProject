#pragma once
#include "gameNode.h"
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
};

