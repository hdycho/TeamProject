#pragma once
#include "enemy.h"

class bomberman : public enemy
{
private:
	int cnt = 1;
	bool _isMotion = false;
	int moveCnt = 1; //처음에 한번 움직여주기위해
public:
	bomberman();
	~bomberman();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();		//모조리 그려짐

	virtual void move();
	virtual void draw();		//
	virtual void enemyCollision();
};

