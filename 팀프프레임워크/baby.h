#pragma once
#include "enemy.h"

class baby : public enemy
{
private:
	float getTime;
public:
	baby();
	~baby();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();		//������ �׷���

	virtual void move();
	virtual void draw();		//�׷��ִ� �Լ�
};

