#pragma once
#include "gameNode.h"
class EditScene:public gameNode
{
private:
	struct Object
	{
		image*img;
		RECT rc;
		int x,y;
		string objName;

		Object(image*_img, int _x, int _y, string name)
			:img(_img),x(_x),y(_y),objName(name){}
	};
private:
	RECT rc;
	Object*Item[2];		//	È­¸é¿¡ Âï´Â³ð

public:
	EditScene();
	~EditScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//Å×½ºÆ®¿ë
	void CamMove(int speed);
	void CamRender();
};

