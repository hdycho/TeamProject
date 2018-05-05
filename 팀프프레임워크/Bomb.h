#pragma once
#include "Obstacle.h"
class Bomb :public Obstacle
{
private:

public:
	Bomb();
	~Bomb();

	virtual HRESULT init(int _x, int _y, string oName);
	virtual void ObstacleUpdate();
};

