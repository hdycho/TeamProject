#pragma once
#include "gameNode.h"


enum ITEMTYPES
{
	POTION_HP,
	POTION_MP,
	GOLD_ITEM
};
class Item : public gameNode
{

protected:
	image * _img;			//이미지 추가
	RECT _rc;				//렉트(충돌에 쓰임)
	ITEMTYPES _itemTypes;	//아이템 종류에 따라
	float _x, _y;
	bool _isShow;			//상태 보여주기

public:

	Item();
	~Item();

	HRESULT init(image* img, ITEMTYPES itemTypes, float x, float y);
	void release();
	void update();
	void render();

	inline ITEMTYPES&GetItemType() { return _itemTypes; }
	inline bool&GetShowState() { return _isShow; }
	inline RECT&GetRect() { return _rc; }
};

