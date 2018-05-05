#pragma once
#include "gameNode.h"
#include "Wood.h"
#include "Iron.h"
#include "Bomb.h"
#include <vector>
class ObstacleManager :public gameNode
{
private:
	vector<Obstacle*>			obsVec;
	vector<Obstacle>::iterator	obsIter;
public:
	ObstacleManager();
	~ObstacleManager();

	HRESULT init();
	void render();
	void update();
	void release();

	void LoadObstacle();
};

