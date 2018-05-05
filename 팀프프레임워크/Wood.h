#pragma once
#include "Obstacle.h"
class Wood :public Obstacle
{
private:
	float pushPower;
public:
	Wood();
	~Wood();

	virtual HRESULT init(int _x, int _y, string oName);
	virtual void ObstacleUpdate();
};

