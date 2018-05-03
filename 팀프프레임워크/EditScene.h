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
		bool isMove;	//	Ŭ���ϸ� ���콺����ٴϰ�
						//	�ƴϸ� ����
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
	Object*Item[2];		//	ȭ�鿡 ��³�
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

	//�׽�Ʈ��
	void CamMove(int speed);
	void CamRender();
};

