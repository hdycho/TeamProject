#pragma once
#include "enemy.h"

class boomerang : public enemy
{

public:
	boomerang();
	~boomerang();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void draw();
	virtual void enemyCollision();
};

