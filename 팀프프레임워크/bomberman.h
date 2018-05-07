#pragma once
#include "enemy.h"

class bomberman : public enemy
{
private:
	int cnt = 1;
	bool _isMotion = false;
	int moveCnt = 1; //ó���� �ѹ� �������ֱ�����
public:
	bomberman();
	~bomberman();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();		//������ �׷���

	virtual void move();
	virtual void draw();		//
	virtual void enemyCollision();
};

