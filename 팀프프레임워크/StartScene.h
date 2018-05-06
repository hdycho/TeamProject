#pragma once
#include "gameNode.h"
#include "button.h"
class StartScene:public gameNode
{
private:
	RECT rc;
	button*start;
	button*edit;
	button*score;

	image*fadeout;

	int alpha;
	
	vector<string>		scoreVec;
public:
	StartScene();
	~StartScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

