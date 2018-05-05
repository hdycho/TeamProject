#pragma once
#include "Obstacle.h"
class Bomb :public Obstacle
{
private:
	bool isCollision;
	float angle;
public:
	Bomb();
	~Bomb();

	virtual HRESULT init(int _x, int _y, string oName);
	virtual void ObstacleUpdate();
};

