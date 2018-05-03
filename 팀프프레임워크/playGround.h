#pragma once
#include "gameNode.h"
#include "GameScene.h"
#include "StartScene.h"
#include "EditScene.h"
class playGround : public gameNode
{
private:
	GameScene*gameScene;
	StartScene*startScene;
	EditScene*editScene;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	playGround();
	~playGround();
};

