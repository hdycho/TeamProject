#pragma once
#include "gameNode.h"
class Obstacle :public gameNode
{
protected:
	image*img;
	RECT rc;
	string oName;
	int x, y;
	bool isShow;
public:
	Obstacle();
	~Obstacle();

	virtual HRESULT init(int _x, int _y, string oName);
	void render();
	void update();
	void release();

	virtual void ObstacleUpdate() = 0;

	inline bool&GetShowState() { return isShow; }
};

