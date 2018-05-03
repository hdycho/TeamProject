#pragma once
#include "gameNode.h"
#include "button.h"
#include <vector>
class EditScene:public gameNode
{
private:
	struct Object
	{
		image*img;
		RECT rc;
		int x,y;
		string objName;
		bool isClick;
		bool isMove;	//	클릭하면 마우스따라다니고
						//	아니면 고정
		bool isShow;
		Object() {}
		Object(image*_img, int _x, int _y, string name)
			:img(_img),x(_x),y(_y),objName(name)
		{
			isClick = false;
			isMove = false;
			isShow = false;
		}
	};
private:
	RECT rc;
	Object*Item[2];		//	화면에 찍는놈
	Object*clickObj;

	vector<Object*>				objVec;
	vector<Object*>::iterator	objIter;
	int itemIdx;

	button*save;
public:
	EditScene();
	~EditScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void SelectObj();
	void DropObj();
	void EditDraw();
	void SaveObj();

	//테스트용
	void CamMove(int speed);
	void CamRender();
};

