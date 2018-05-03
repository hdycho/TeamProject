#pragma once
#include "gameNode.h"
#include "button.h"
class StartScene:public gameNode
{
private:
	RECT rc;
	button*start;
	button*edit;
	
public:
	StartScene();
	~StartScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

