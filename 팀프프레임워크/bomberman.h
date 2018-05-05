#pragma once
#include "enemy.h"

class bomberman : public enemy
{
private:

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

