#pragma once
#include "gameNode.h"
#include "GameScene.h"
#include "StartScene.h"
class playGround : public gameNode
{
private:
	GameScene*gameScene;
	StartScene*startScene;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

