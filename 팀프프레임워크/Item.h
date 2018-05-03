#pragma once
#include "gameNode.h"
#include "PixelCol.h"

enum ITEMTYPES
{
	POTION_HP,
	POTION_MP,
	GOLD_ITEM
};
class Item : public gameNode
{
private:
	enum GOLDSTATE
	{
		GOLD_AIR,
		GOLD_GROUND
	};

protected:
	image * _img;
	PixelCol* _pc;
	RECT _rc;
	ITEMTYPES _itemTypes;
	GOLDSTATE gState;
	int _x, _y;
	int _count, _index;
	float gravity;
	float jumpPower;
	bool _isShow;
	bool _isCollision;

public:

	Item();
	~Item();

	HRESULT init(image* img, ITEMTYPES itemTypes, int x, int y);
	void release();
	void update();
	void render();
	void GoldUpdate();

	inline ITEMTYPES&GetItemType() { return _itemTypes; }
	inline RECT&GetRect() { return _rc; }
	inline bool&GetShowState() { return _isShow; }
	inline bool&GetCollision() { return _isCollision; }
};

