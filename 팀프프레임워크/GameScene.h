#pragma once
#include "gameNode.h"
class GameScene:public gameNode
{
private:
	//객체들 넣어서 사용하면 됩니다.
	RECT rc;
	RECT rc2;
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

