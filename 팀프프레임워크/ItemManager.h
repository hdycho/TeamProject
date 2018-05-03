#pragma once
#include "gameNode.h"
#include "Item.h"
#include <vector>

class ItemManager : public gameNode
{
private:
	typedef vector<Item*> vItem;

private:
	vItem _vMapItem;
	vItem _vGold;

private:
	int index;
	int GoldUp[30], GoldDown[30];

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void DropGold(int x, int y, int goldUp, int goldDown);
	void GroundCollision();

	inline vItem&GetMapItemVec() { return _vMapItem; }
	inline vItem&GetGoldItecVec() { return _vGold; }
};

