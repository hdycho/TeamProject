#pragma once
#include "gameNode.h"
#include "button.h"
class GameOverScene :public gameNode
{
private:
	button*Loby;
	button*Quit;

	image*fadeout;
	int alpha;

	bool sceneChange;
	int metaData;
	string time;
public:
	GameOverScene();
	~GameOverScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void LoadTime();
};

