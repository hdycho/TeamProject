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
	image * _img;			//�̹��� �߰�
	RECT _rc;				//��Ʈ(�浹�� ����)
	ITEMTYPES _itemTypes;	//������ ������ ����
	float _x, _y;
	bool _isShow;			//���� �����ֱ�

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

