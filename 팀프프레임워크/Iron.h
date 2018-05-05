#pragma once
#include "Obstacle.h"
class Iron :public Obstacle
{
private:

public:
	Iron();
	~Iron();

	virtual HRESULT init(int _x, int _y, string oName);
	virtual void ObstacleUpdate();
};

