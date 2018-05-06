#pragma once
#include "gameNode.h"
#include "button.h"
class ClearScene :public gameNode
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
	ClearScene();
	~ClearScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void LoadTime();
};

