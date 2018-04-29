#pragma once
#include "gameNode.h"
#include "GameScene.h"
class playGround : public gameNode
{
private:
	GameScene*gameScene;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

