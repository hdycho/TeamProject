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

	int _index;

public:
	ItemManager();
	~ItemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void DropGold(int x, int y);

	inline vItem&GetMapItemVec() { return _vMapItem; }
	inline vItem&GetGoldItecVec() { return _vGold; }
};

