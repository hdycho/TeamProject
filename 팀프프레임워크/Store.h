#pragma once
#include "gameNode.h"
#include "GameScene.h"

class GameScene;
enum ITEMTYPE {
	WEAPON,
	AMOR,
	POTION,
	ACCESSORY,
	GOLD,
	MAGIC_BOOK,
	SKILL_ITEM
};

enum BUTTONTYPE {
	FAIL = -1,
	BACK_BUTTON,
	BUY_BUTTON
};

struct ITEM
{
	image*		image;
	string		itemName;
	ITEMTYPE	itemType;
	int			salePrice;
	int			stock;

	float		x, y;
	RECT		rc;
	bool		isSell;
};

struct BUTTON
{
	image*		image;
	string		buttonName;

	BUTTONTYPE	buttonType;
	float		x, y;
	RECT		rc;
};

class Store : public gameNode
{
private:
	vector<ITEM*> _vItem;
	//	vector<ITEM*>::iterator _viItem;
	vector<BUTTON*> _vButton;

	//=========== 상점 변수 ============
	image*		_image;
	float		_x, _y;
	RECT		_rc;
	int			_index;
	int*		_money;
	GameScene*	_gc;
	ITEM*		_temp;
	//==================================
public:
	char*		_message;

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	ITEM* Store::buyItem(int index, int* money);
	BUTTONTYPE Store::buttonCollision(int* pIndex);
	void setLinkMoney(int* money) { this->_money = money; }
	void setGameSceneAddress(GameScene* gc) { _gc = gc; }

	Store();
	~Store();
};