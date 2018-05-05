#pragma once
#include "enemy.h"


class bug : public enemy
{
private:


public:
	bug();
	~bug();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	//virtual HRESULT init(int x, int y, player* player);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();		//모조리 그려짐

	virtual void move();
	virtual void draw();		//그려주는 함수
	virtual void enemyCollision();
};

