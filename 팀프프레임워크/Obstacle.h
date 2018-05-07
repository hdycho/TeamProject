#pragma once
#include "gameNode.h"

class player;
class Obstacle :public gameNode
{
protected:
	image*img;
	RECT rc;
	string oName;
	int x, y;
	bool isShow;

	player*p;
public:
	Obstacle();
	~Obstacle();

	virtual HRESULT init(int _x, int _y, string oName);
	void render();
	void update();
	void release();

	virtual void ObstacleUpdate() = 0;

	inline bool&GetShowState() { return isShow; }
	inline RECT&getRect() { return rc; }
	inline void LinkPlayer(player*_p) { p = _p; }
};

