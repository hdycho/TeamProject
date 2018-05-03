#pragma once
#include "gameNode.h"


class button : public gameNode
{
private:
	enum BUTTONSTATE
	{
		BUTTON_DOWN,
		BUTTON_UP,
		BUTTON_NULL
	};
private:
	BUTTONSTATE bState;
	image*img;
	RECT rc;
	float x, y;

	int frameX;
	bool isClick;

	string buttonName;


public:
	button();
	~button();

	//��ư����ϱ� ���ؼ� �̸����������Ѵ�
	HRESULT Init(image*img, string bName, float x, float y);
	void Render();
	void Update(int key, bool isUseCam);
	void Release();

	void ButtonNameDraw();

	inline bool IsClick() { return isClick; }
	inline RECT&GetRect() { return rc; }
};
