#pragma once
#include "gameNode.h"
class GameScene:public gameNode
{
private:
	//��ü�� �־ ����ϸ� �˴ϴ�.
	RECT rc;
	RECT rc2;
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

